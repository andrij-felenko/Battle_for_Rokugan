#ifndef LIB_BFR_KARTA_REGION_H
#define LIB_BFR_KARTA_REGION_H

#include "bfrLib_pre.h"

class battle_for_rokugan::karta::Territory : public QObject
{
    Q_OBJECT
public:
    Territory(TerritoryType type, QObject* parent);
    Q_ENUM(TerritoryType)

    ClanType daimyo() const;
    int provinceOwnerCount(ClanType type) const;
    Province* capital() const;

    Province* operator[](unsigned number) const;

    TerritoryType type() const;

    static bool isShadow(TerritoryType type);
    unsigned provinceCount() const;

private:
    TerritoryType m_type;
    bool m_firstCard;
    ProvinceList m_provinceList;

    void addProvinces(char_v list, char capital = -1, char_v navyList = {});
    Province* findProvince(uchar number);

    friend class Map;
    friend class object::SecretObjective;
};

namespace battle_for_rokugan {
    TerritoryType operator+ (TerritoryType type, unsigned i);
    TerritoryType operator++(TerritoryType type);
}

#endif
