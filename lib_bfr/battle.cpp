#include "lib_bfr/battle.h"
#include "lib_bfr/player.h"
#include "lib_bfr/map.h"

BattleForRokugan::Battle::Battle(Map *map, QObject *parent)
    : QObject(parent), m_map(map)
{
    //
}

void BattleForRokugan::Battle::reset(PlayerList playerList)
{
    m_playerList = playerList;
}

void BattleForRokugan::Battle::run()
{
    // TODO
    // emit battleFinished
}
