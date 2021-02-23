#include "lib_bfr/border.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/player.h"
#include "lib_bfr/province.h"
#include "lib_bfr/provinceToken.h"

BFR::Province::Province(RegionType region, bool capital, bool navy,
                   uchar number, uchar stars, QObject *parent)
    : QObject(parent),
      m_capital(capital),
      m_navy(navy),
      m_number(number),
      m_stars(stars),
      m_defends(capital ? 2 : 0),
      m_region(region)
{
    //
}

BFR::ClanType BattleForRokugan::Province::clanType() const
{
    if (auto pl = owner(); pl)
        return pl->clan()->type();
    return ClanType::None;
}

uchar BFR::Province::stars() const
{
    uchar ret = m_stars;
    for (const auto &it : m_tokenList)
        switch (it->type()) {
        case ProvinceTokenType::ControlOn: ret++; break;
        case ProvinceTokenType::HonorBonus: ret += (4 - m_stars); break;
        default:;
        }
    return ret;
}

bool BFR::Province::scorched() const
{
    for (auto it : m_tokenList)
        if (it->type() == ProvinceTokenType::ScorchedEarth)
            return true;
    return false;
}

uchar BFR::Province::number() const
{
    return m_number;
}

uchar BFR::Province::defends() const
{
    uchar ret = m_defends;
    for (const auto &it : m_tokenList)
        switch (it->type()) {
        case ProvinceTokenType::ControlOn: ret++; break;
        case ProvinceTokenType::ProtectionBonus: ret += 2; break;
        default:;
        }
    return ret;
}

BFR::RegionType BFR::Province::region() const
{
    return m_region;
}

uchar BFR::Province::controlUp() const
{
    unsigned ret = 0;
    for (const auto &it : m_tokenList)
        if (it->type() == ProvinceTokenType::ControlOn)
            ret++;
    return ret;
}

void BFR::Province::addBorder(Border* border)
{
    m_borderList.push_back(border);
}

BFR::ProvinceList BFR::Province::neighboringProvinces() const
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

BFR::Player* BFR::Province::owner() const
{
    if (not m_player)
        return nullptr;
    return m_player;
}

void BFR::Province::setOwner(Player* newOwner)
{
    // TODO check is it good line to emit remove province from player list
    m_player = newOwner;
    // TODO emit owner changed
}

bool BFR::Province::capital() const
{
    return m_capital;
}

bool BFR::Province::navy() const
{
    if (m_navy)
        return true;
    for (const auto &it : m_tokenList)
        if (it->type() == ProvinceTokenType::Harbor)
            return true;
    return false;
}
