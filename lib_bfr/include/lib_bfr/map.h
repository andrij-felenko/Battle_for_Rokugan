#ifndef LIB_BFR_MAP_H
#define LIB_BFR_MAP_H

#include "bfrLib_pre.h"
#include <array>

class BattleForRokugan::Map : public QObject
{
    Q_OBJECT
public:
    Map(QObject* parent);

    Region* operator[](const RegionType type) const;
    void clear();

private:
    RegionList m_regionList;
    BorderList m_listBorders;

    inline bool addBorder(RegionType type, uchar_v v);
    inline bool addBorder(RegionType type1, unsigned char s1,
                          RegionType type2, unsigned char s2 = 0);
    inline bool addBorder(RegionType type1, uchar_v s1,
                          RegionType type2, uchar_v s2);
    inline bool addBorder(RegionType type, uchar_pair_v v);
    inline bool addBorder(RegionType type1, RegionType type2, uchar_pair_v v);

    Province* findProvince(RegionType type, unsigned char stars) const;
    Region*   findRegion  (RegionType type) const;

    inline void addLandBorder();
    inline void addNavyBorder();

    friend class Game;
    friend class Mission;
};

#endif // LIB_BFR_MAP_H
