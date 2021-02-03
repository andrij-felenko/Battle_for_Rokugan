#ifndef LIB_BFR_GAME_H
#define LIB_BFR_GAME_H

#include <QtCore/QObject>
#include "gameMap.h"

namespace BattleForRokugan {
    class Game;
}

class BattleForRokugan::Game : public QObject
{
    Q_OBJECT
public:
    enum class PlaceType{
        //
    };
    enum class Phase : unsigned char {
        Pregame = 0,
        FirstTurn,
        SecondTurn,
        ThirdTurn,
        FourthTurn,
        FiveTurn,
        Postgame = 7
    }; Q_ENUM(Phase)

    Game(QObject* parent = nullptr);

private:
    GameMap m_map;
};

#endif // LIB_BFR_Game_H
