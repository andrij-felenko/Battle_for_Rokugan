#ifndef LIB_BFR_HANDLER_BATTLE_H
#define LIB_BFR_HANDLER_BATTLE_H

#include "bfrLib_pre.h"

class battle_for_rokugan::handler::Battle : public QObject
{
    Q_OBJECT
public:
    Battle(karta::Map* map, QObject* parent);

    void reset(object::PlayerList playerList);
    void run();

signals:
    void battleFinished();

private:
    karta::Map* m_map;
    object::PlayerList m_playerList;

    inline void removeNotFormatPlaced();
    inline void scorcheEarthAndDiplomacy();
    inline void calculateBattle(karta::Province* province);
};

#endif
