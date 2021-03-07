#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"
#include "lib_bfr/token/control.h"
#include "lib_bfr/token/province.h"

BFR::Karta::Province::Province(TerritoryType region, bool capital, bool navy,
                   uchar number, uchar stars, QObject *parent)
    : TokenBasement(parent),
      m_capital(capital),
      m_navy(navy),
      m_number(number),
      m_stars(stars),
      m_defends(capital ? 2 : 0),
      m_region(region)
{
    //
}

BFR::ClanType BFR::Karta::Province::clanType() const
{
    if (auto pl = owner(); pl)
        return pl->clan()->type();
    return ClanType::None;
}

uchar BFR::Karta::Province::stars() const
{
    uchar ret = m_stars;
    for (const auto &it : m_statusList)
        if (it->type() == ProvinceTokenType::HonorBonus)
            ret += (4 - m_stars);

    for (const auto &it : m_ctrlTokenList)
        ret += it->stars();

    return ret;
}

bool BFR::Karta::Province::scorched() const
{
    for (auto it : m_statusList)
        if (it->type() == ProvinceTokenType::ScorchedEarth)
            return true;
    return false;
}

uchar BFR::Karta::Province::number() const
{
    return m_number;
}

uchar BFR::Karta::Province::defends() const
{
    uchar ret = m_defends;
    for (const auto &it : m_statusList)
        if (it->type() == ProvinceTokenType::ProtectionBonus)
            ret += 2;

    for (const auto &it : m_ctrlTokenList)
        ret += it->defends();

    return ret;
}

BFR::TerritoryType BFR::Karta::Province::region() const
{
    return m_region;
}

uchar BFR::Karta::Province::controlUp() const
{
    unsigned ret = 0;
    for (const auto &it : m_ctrlTokenList)
        if (it->isOn())
            ret++;
    return ret;
}

void BFR::Karta::Province::addBorder(Border* border)
{
    m_borderList.push_back(border);
}

BFR::Karta::ProvinceList BFR::Karta::Province::neighboringProvinces() const
{
    ProvinceList list;
    for (auto it : m_borderList){
        if (it->province1() != this && it->province1() != nullptr)
            list.push_back(it->province1());
        if (it->province2() != this && it->province2() != nullptr)
            list.push_back(it->province2());
    }
    return list;
}

void BattleForRokugan::Karta::Province::addControlOnToken(uint count)
{
    if (not m_player)
        return;

    auto clanType = m_player->clan()->type();
    for (uint i = 0; i < count; i++)
        m_ctrlTokenList.push_back(new Token::Control(true, clanType, this));
    emit ctrlTokenCountChanged();
}

void BFR::Karta::Province::setProvinceToken(ProvinceTokenType type)
{
    m_statusList.push_back(new Token::Province(m_player, type));

    if (type ==ProvinceTokenType::ScorchedEarth)
        emit scorchedStatusChanged(true);
}

bool BFR::Karta::Province::provinceTokenContains(ProvinceTokenType type)
{
    for (auto it : m_statusList)
        if (it->type() == type)
            return true;
    return false;
}

void BFR::Karta::Province::clearCombatToken(bool withBorders)
{
    removeCombatToken(m_combatList);
    if (not withBorders)
        return;

    for (auto it : m_borderList)
        it->removeCombatToken(it->m_combatList);
}

BFR::Object::Player* BFR::Karta::Province::owner() const
{
    if (not m_player)
        return nullptr;

    return m_player;
}

void BFR::Karta::Province::setOwner(Object::Player* newOwner)
{
    if (newOwner == m_player)
        return;

    m_player = newOwner;

    for (auto it : m_ctrlTokenList)
        it->deleteLater();

    m_ctrlTokenList.clear();
    emit ctrlTokenCountChanged();
    if (m_player){
        auto ctrl = new Token::Control(false, m_player->clan()->type(), this);
        m_ctrlTokenList.push_back(ctrl);
    }

    emit ownerChanged(m_player);
}

bool BFR::Karta::Province::capital() const
{
    return m_capital;
}

bool BFR::Karta::Province::navy() const
{
    if (m_navy)
        return true;
    for (const auto &it : m_statusList)
        if (it->type() == ProvinceTokenType::Harbor)
            return true;
    return false;
}
