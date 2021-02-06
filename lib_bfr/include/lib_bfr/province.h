#ifndef LIB_BFR_PROVINCE_H
#define LIB_BFR_PROVINCE_H

#include "region.h"
#include "clan.h"
#include "provinceToken.h"

namespace BattleForRokugan {
    class Province;
    class Border;
}

class BattleForRokugan::Province
{
public:
    Province(Region::Type region, bool capital, bool navy, unsigned char number, unsigned char stars);

    Clan::Type clanOwner() const;
    void setClanOwner(const Clan::Type &clanOwner);

    bool capital() const;
    bool navy() const;
    unsigned char defends() const;
    unsigned char number() const;
    unsigned char stars() const;
    Region::Type region() const;

    unsigned controlUp() const;

    void addBorder(Border* border);
    std::list <std::shared_ptr <Province>> neighboringProvinces() const;

private:
    bool m_capital;
    bool m_navy;
    unsigned char m_number;
    unsigned char m_stars;
    unsigned char m_defends;
    Region::Type m_region;
    Clan::Type m_clanOwner;
    std::list <std::shared_ptr <ProvinceToken>> m_tokenList;
    std::vector <Border*> m_borderList;
};

#endif // LIB_BFR_PROVINCE_H
