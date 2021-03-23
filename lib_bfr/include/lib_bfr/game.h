#ifndef LIB_BFR_GAME_H
#define LIB_BFR_GAME_H

#include "bfrLib_pre.h"

class battle_for_rokugan::Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isCanStart READ checkIsCanStart NOTIFY isCanStartChanged)
public:
    Game(QObject* parent = nullptr);
    virtual ~Game();
    Q_ENUM(Phase)

    void addPlayer(QString name, ClanType clan = ClanType::None);
    void removePlayer(ClanType clan);

    void start();
    void init();
    void reinit();

signals:
    void isCanStartChanged(bool);
    void secretObjectiveAdded();

private:
    karta::Map* m_map;
    handler::Turn* m_turns;

    void clear();
    bool checkIsCanStart();

    object::CardList m_cardPocket;
    object::PlayerList m_playerList;
    object::SecretObjectiveList m_secretObjectiveList;
    handler::Stats* m_stats;
    handler::Battle* m_battle;
};

#endif // LIB_BFR_Game_H
