#include "lib_bfr/province.h"
#include "lib_bfr/border.h"

BattleForRokugan::Province::Province(Region::Type region, bool capital, bool navy,
                                     unsigned char number, unsigned char stars)
    : m_capital(capital), m_navy(navy), m_number(number), m_stars(stars),
      m_defends(capital ? 2 : 0), m_region(region)
{
    //
}

unsigned char BattleForRokugan::Province::stars() const
{
    unsigned char ret = m_stars;
    for (auto it = m_tokenList.begin(); it != m_tokenList.end(); ++it)
        switch (it->get()->type()) {
        case ProvinceToken::Type::ControlOn: ret++; break;
        case ProvinceToken::Type::HonorBonus: ret += (4 - m_stars); break;
        default:;
        }
    return ret;
}

unsigned char BattleForRokugan::Province::number() const
{
    return m_number;
}

unsigned char BattleForRokugan::Province::defends() const
{
    unsigned char ret = m_defends;
    for (auto it = m_tokenList.begin(); it != m_tokenList.end(); ++it)
        switch (it->get()->type()) {
        case ProvinceToken::Type::ControlOn: ret++; break;
        case ProvinceToken::Type::ProtectionBonus: ret += 2; break;
        default:;
        }
    return ret;
}

BattleForRokugan::Region::Type BattleForRokugan::Province::region() const
{
    return m_region;
}

unsigned BattleForRokugan::Province::controlUp() const
{
    unsigned ret = 0;
    for (const auto &it : m_tokenList)
        if (it.get()->type() == ProvinceToken::Type::ControlOn)
            ret++;
    return ret;
}

void BattleForRokugan::Province::addBorder(Border *border)
{
    m_borderList.push_back(border);
}

std::list<std::shared_ptr<BattleForRokugan::Province>> BattleForRokugan::Province::neighboringProvinces() const
{
    std::list<std::shared_ptr<BattleForRokugan::Province>> list;
    for (auto it : m_borderList){
        if (it->province1().get() != this && it->province1().get() != nullptr)
            list.push_back(it->province1());
        if (it->province2().get() != this && it->province2().get() != nullptr)
            list.push_back(it->province2());
    }
    return list;
}

BattleForRokugan::Clan::Type BattleForRokugan::Province::clanOwner() const
{
    return m_clanOwner;
}

void BattleForRokugan::Province::setClanOwner(const Clan::Type &clanOwner)
{
    m_clanOwner = clanOwner;
}

bool BattleForRokugan::Province::capital() const
{
    return m_capital;
}

bool BattleForRokugan::Province::navy() const
{
    if (m_navy)
        return true;
    for (const auto &it : m_tokenList)
        if (it.get()->type() == ProvinceToken::Type::Harbor)
            return true;
    return false;
}
