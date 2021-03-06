#ifndef LIB_BFR_BATTLE_H
#define LIB_BFR_BATTLE_H

#include "bfrLib_pre.h"

class BattleForRokugan::Battle : public QObject
{
    Q_OBJECT
public:
    Battle(Map* map, QObject* parent);

    void reset(PlayerList playerList);
    void run();

signals:
    void battleFinished();

private:
    Map* m_map;
    PlayerList m_playerList;

    inline void removeNotFormatPlaced();
    inline void scorcheEarthAndDiplomacy();
    inline void calculateBattle(Province* province);
};

#endif // LIB_BFR_BATTLE_H
