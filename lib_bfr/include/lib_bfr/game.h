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

    ErrorMsg start();
    void init();
    void reinit();

    array_u7 getClanControlToken() const;
    array_u7 getClanProvinceOwned() const;
    array_u7 getRegionCardOwner() const;

//    MapPtr map() const;

signals:
    bool isCanStartChanged();
    void missionAdded();

private:
    int m_turn;
    Phase m_phase;
    Map* m_map;

    ClanType getCurrentFirstPlayer();
    void updatePlayerPosition();
    void updateTurnQueue();
    void clear();
    bool checkIsCanStart();

    CardTypeList m_firstList;
    CardList m_cardPocket;
    PlayerList m_playerList;
    MissionList m_missionList;
    ClanStats* m_stats;
};

#endif // LIB_BFR_Game_H
