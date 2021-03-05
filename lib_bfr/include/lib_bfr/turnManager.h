#ifndef LIB_BFR_TURN_MANAGER_H
#define LIB_BFR_TURN_MANAGER_H

#include "bfrLib_pre.h"

class BattleForRokugan::TurnManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int turn     READ turn     NOTIFY turnChanged)
    Q_PROPERTY(int position READ position NOTIFY positionChanged)
public:
    TurnManager(ClanStats* stats, QObject* parent);

    void nextTurn();
    void reset(PlayerList list);
    void clear();

    int turn()     const { return m_turn; }
    int position() const { return m_position; }

signals:
    void gameFinished();
    void turnPlacedFinished();

    void turnChanged    (int turn);
    void positionChanged(int position);

private:
    ClanType getCurrentFirstPlayer();
    void updateTurnQueue();
    void nextPosition();

    int m_turn;
    int m_subTurnLeft;
    int m_position;
    Phase m_phase;

    CardTypeList m_firstList;
    PlayerList m_playerList;
    ClanStats* m_stats;
    Card* m_firstCard;
};

#endif // LIB_BFR_TURN_MANAGER_H
