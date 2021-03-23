#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"
#include "lib_bfr/token/control.h"
#include "lib_bfr/token/honor.h"
#include "lib_bfr/token/province.h"

bfr::karta::Province::Province(TerritoryType territory, bool capital, bool navy,
                   uchar number, uchar stars, QObject *parent)
    : TokenBasement(parent),
      m_capital(capital),
      m_navy(navy),
      m_number(number),
      m_stars(stars),
      m_defends(capital ? 2 : 0),
      m_territory(territory)
{
    //
}

bfr::ClanType bfr::karta::Province::clanType() const
{
    if (auto pl = owner(); pl)
        return pl->clan()->type();
    return ClanType::None;
}

uchar bfr::karta::Province::stars() const
{
    uchar ret = m_stars;
    for (const auto &it : m_ctrlTokenList)
        ret += it->stars();

    for (const auto &it : m_statusList)
        if (it->type() == ProvinceTokenType::HonorBonusFull){
            ret += (4 - m_stars);
            return ret;
        }

    for (const auto &it : m_honorList)
        ret += it->honor();

    return ret;
}

bool bfr::karta::Province::scorched() const
{
    for (auto it : m_statusList)
        if (it->type() == ProvinceTokenType::ScorchedEarth)
            return true;
    return false;
}

uchar bfr::karta::Province::number() const
{
    return m_number;
}

uchar bfr::karta::Province::defends() const
{
    uchar ret = m_defends;
    for (const auto &it : m_statusList){
        if (it->type() == ProvinceTokenType::ProtectionBonus2)
            ret += 2;
        else if (it->type() == ProvinceTokenType::ProtectionBonus)
            ret++;
    }

    for (const auto &it : m_ctrlTokenList)
        ret += it->defends();

    return ret;
}

bfr::TerritoryType bfr::karta::Province::territory() const
{
    return m_territory;
}

uchar bfr::karta::Province::controlUp() const
{
    unsigned ret = 0;
    for (const auto &it : m_ctrlTokenList)
        if (it->isOn())
            ret++;
    return ret;
}

void bfr::karta::Province::addBorder(Border* border)
{
    m_borderList.push_back(border);
}

bfr::karta::ProvinceList bfr::karta::Province::neighboringProvinces() const
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

void bfr::karta::Province::addControlOnToken(uint count)
{
    if (not m_player)
        return;

    auto clanType = m_player->clan()->type();
    for (uint i = 0; i < count; i++)
        m_ctrlTokenList.push_back(new token::Control(true, clanType, this));
    emit ctrlTokenCountChanged();
}

void bfr::karta::Province::popControlToken()
{
    auto isRemoveSmth = std::remove_if(m_ctrlTokenList.begin(), m_ctrlTokenList.end(),
                                       [](token::Control* token){
            if (token->isOn()){
                token->deleteLater();
                return true;
            }
            return false;
    });
    if (isRemoveSmth != m_ctrlTokenList.end())
        m_ctrlTokenList.erase(isRemoveSmth, m_ctrlTokenList.end());
    else if (m_ctrlTokenList.count() > 0){
        m_ctrlTokenList.first()->deleteLater();
        m_ctrlTokenList.removeFirst();
    }
    emit ctrlTokenCountChanged();
}

void bfr::karta::Province::pushHonor(uint value)
{
    m_honorList.push_back(new token::Honor(value, this));
}

void bfr::karta::Province::setProvinceToken(ProvinceTokenType type)
{
    m_statusList.push_back(new token::Province(m_player, this, type));

    if (type ==ProvinceTokenType::ScorchedEarth)
        emit scorchedStatusChanged(true);
}

void bfr::karta::Province::removeProvinceToken(ProvinceTokenType type)
{
    m_statusList.erase(
                std::remove_if(m_statusList.begin(), m_statusList.end(),
                               [type](token::Province* token)
                {
                    if (token->type() == type){
                        token->deleteLater();
                        return true;
                    }
                    return false;
                }),
            m_statusList.end());
}

bool bfr::karta::Province::provinceTokenContains(ProvinceTokenType type)
{
    for (auto it : m_statusList)
        if (it->type() == type)
            return true;
    return false;
}

void bfr::karta::Province::clearCombatToken(bool withBorders)
{
    removeCombatToken(m_combatList);
    if (not withBorders)
        return;

    for (auto it : m_borderList)
        it->removeCombatToken(it->m_combatList);
}

bool bfr::karta::Province::isShadowProvince() const
{
    return m_territory == TerritoryType::ShadowlandsNorth ||
            m_territory == TerritoryType::ShadowlandsSouth;
}

void bfr::karta::Province::swapAllContent(bfr::karta::Province *province)
{
    std::swap(m_combatList, province->m_combatList);
    std::swap(m_ctrlTokenList, province->m_ctrlTokenList);
    std::swap(m_statusList, province->m_statusList);
    std::swap(m_player, province->m_player);

    emit ownerChanged(m_player);
    emit ctrlTokenCountChanged();
    emit scorchedStatusChanged(scorched());
}

bfr::object::Player* bfr::karta::Province::owner() const
{
    if (not m_player)
        return nullptr;

    return m_player;
}

void bfr::karta::Province::setOwner(object::Player* newOwner)
{
    if (newOwner == m_player)
        return;

    m_player = newOwner;

    for (auto it : m_ctrlTokenList)
        it->deleteLater();

    m_ctrlTokenList.clear();
    emit ctrlTokenCountChanged();
    if (m_player){
        auto ctrl = new token::Control(false, m_player->clan()->type(), this);
        m_ctrlTokenList.push_back(ctrl);
    }

    emit ownerChanged(m_player);
}

bool bfr::karta::Province::capital() const
{
    return m_capital;
}

bool bfr::karta::Province::navy() const
{
    if (m_navy)
        return true;
    for (const auto &it : m_statusList)
        if (it->type() == ProvinceTokenType::Harbor)
            return true;
    return false;
}
