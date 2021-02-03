#include "lib_bfr/province.h"

BattleForRokugan::Province::Province(Region::Type region, bool capital,
                                     unsigned char number, unsigned char stars)
    : m_capital(capital), m_number(number), m_stars(stars),
      m_defends(capital ? 2 : 0), m_region(region)
{
    //
}

unsigned char BattleForRokugan::Province::stars() const
{
    return m_stars;
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

BattleForRokugan::Clan::Type BattleForRokugan::Province::clanOwner() const
{
    return m_clanOwner;
}

void BattleForRokugan::Province::setClanOwner(const Clan::Type &clanOwner)
{
    m_clanOwner = clanOwner;
}
