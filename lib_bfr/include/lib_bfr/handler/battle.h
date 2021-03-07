#ifndef LIB_BFR_HANDLER_BATTLE_H
#define LIB_BFR_HANDLER_BATTLE_H

#include "bfrLib_pre.h"

class BattleForRokugan::Handler::Battle : public QObject
{
    Q_OBJECT
public:
    Battle(Karta::Map* map, QObject* parent);

    void reset(Object::PlayerList playerList);
    void run();

signals:
    void battleFinished();

private:
    Karta::Map* m_map;
    Object::PlayerList m_playerList;

    inline void removeNotFormatPlaced();
    inline void scorcheEarthAndDiplomacy();
    inline void calculateBattle(Karta::Province* province);
};

#endif
