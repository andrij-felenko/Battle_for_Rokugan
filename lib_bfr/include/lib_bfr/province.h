#ifndef LIB_BFR_PROVINCE_H
#define LIB_BFR_PROVINCE_H

#include "region.h"
#include "clan.h"
#include "provinceToken.h"

namespace BattleForRokugan {
    class Province;
}

class BattleForRokugan::Province
{
public:
    Province(Region::Type region, bool capital, unsigned char number, unsigned char stars);

    Clan::Type clanOwner() const;
    void setClanOwner(const Clan::Type &clanOwner);

    bool capital() const;
    unsigned char defends() const;
    unsigned char number() const;
    unsigned char stars() const;
    Region::Type region() const;

private:
    bool m_capital;
    unsigned char m_number;
    unsigned char m_stars;
    unsigned char m_defends;
    Region::Type m_region;
    Clan::Type m_clanOwner;
    std::list <std::shared_ptr <ProvinceToken>> m_tokenList;
};

#endif // LIB_BFR_PROVINCE_H
