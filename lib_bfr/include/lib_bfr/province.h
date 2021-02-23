#ifndef LIB_BFR_PROVINCE_H
#define LIB_BFR_PROVINCE_H

#include "bfrLib_pre.h"

class BattleForRokugan::Province : public QObject
{
    Q_OBJECT
public:
    Province(RegionType region, bool capital, bool navy,
             uchar number, uchar stars, QObject* parent);

    ClanType clanType() const;
    Player* owner() const;
    void setOwner(Player* newOwner);

    bool scorched() const;
    bool capital() const;
    bool navy() const;
    uchar defends() const;
    uchar number() const;
    uchar stars() const;
    RegionType region() const;

    uchar controlUp() const;

    void addBorder(Border* border);
    ProvinceList neighboringProvinces() const;

private:
    bool m_capital;
    bool m_navy;
    uchar m_number;
    uchar m_stars;
    uchar m_defends;

    RegionType m_region;
    Player* m_player;
    ProvinceTokenList m_tokenList;
    BorderList m_borderList;
};

#endif // LIB_BFR_PROVINCE_H
