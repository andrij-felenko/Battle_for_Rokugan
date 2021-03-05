#ifndef LIB_BFR_GAME_H
#define LIB_BFR_GAME_H

#include "bfrLib_pre.h"

class BattleForRokugan::Game : public QObject
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
    void missionAdded();

private:
    Map* m_map;
    TurnManager* m_turns;

    void clear();
    bool checkIsCanStart();

    CardList m_cardPocket;
    PlayerList m_playerList;
    MissionList m_missionList;
    ClanStats* m_stats;
    Battle* m_battle;
};

#endif // LIB_BFR_Game_H
