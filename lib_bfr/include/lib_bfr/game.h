#ifndef LIB_BFR_GAME_H
#define LIB_BFR_GAME_H

#include <QtCore/QObject>
#include "gameMap.h"
#include "player.h"
#include <QtCore/QListIterator>

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
        Pregame,
        Game,
        Postgame
    }; Q_ENUM(Phase)

    Game(QObject* parent = nullptr);

    void addPlayer(QString name, Clan::Type clan = Clan::Type::None);
    void removePlayer(const Clan::Type &clan);
    std::optional<QString> start();

    std::array <unsigned, 7> getClanControlToken() const;
    std::array <unsigned, 7> getClanProvinceOwned() const;
    std::array <unsigned, 7> getRegionCardOwner() const;

private:
    int m_turn;
    Phase m_phase;
    GameMap* m_map;

    QList <Card::Type> m_firstList;
    Clan::Type getCurrentFirstPlayer();

    QList <Player*> m_playerList;
    QList <Player*> m_turnQueue;
    QList <Card*> m_cardPocket;
};

#endif // LIB_BFR_Game_H
