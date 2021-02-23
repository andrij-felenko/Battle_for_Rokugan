#ifndef LIB_BFR_REGION_H
#define LIB_BFR_REGION_H

#include "bfrLib_pre.h"

class BattleForRokugan::Region : public QObject
{
    Q_OBJECT
public:
    Region(RegionType type, QObject* parent);
    Q_ENUM(RegionType)

    ClanType daimyo() const;
    int provinceOwnerCount(ClanType type) const;
    Province* capital() const;

    Province* operator[](unsigned number) const;

    RegionType type() const;

    static bool isShadow(RegionType type);
    unsigned provinceCount() const;

private:
    RegionType m_type;
    bool m_firstCard;
    ProvinceList m_provinceList;

    void addProvinces(char_v list, char capital = -1, char_v navyList = {});
    Province* findProvince(uchar number);

    friend class Map;
    friend class Mission;
};

namespace BattleForRokugan {
    RegionType operator+ (RegionType type, unsigned i);
    RegionType operator++(RegionType type);
}

#endif // LIB_BFR_REGION_H
