#ifndef LIB_BFR_GAMEMAP_H
#define LIB_BFR_GAMEMAP_H

#include <QtCore/QObject>
#include "region.h"
#include "border.h"
#include <optional>

namespace BattleForRokugan {
    class GameMap;
}

class BattleForRokugan::GameMap : public QObject
{
    Q_OBJECT
public:
    GameMap(QObject* parent = nullptr);

private:
    QList <Region*> m_regionList;
    QList <Border*> m_listBorders;

    bool addBorder(Region::Type type, uchar number = 0);
    bool addBorder(Region::Type type1, unsigned char s1, Region::Type type2, unsigned char s2 = 0);
    std::optional <std::shared_ptr <Province>> findProvince(Region::Type type, unsigned char stars) const;
    std::optional <Region*> findRegion(Region::Type type) const;

    inline void addLandBorder();
    inline void addNavyBorder();
};

#endif // LIB_BFR_GAMEMAP_H