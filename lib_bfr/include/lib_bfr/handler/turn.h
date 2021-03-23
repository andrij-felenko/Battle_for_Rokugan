#ifndef LIB_BFR_HANDLER_TURN_H
#define LIB_BFR_HANDLER_TURN_H

#include "bfrLib_pre.h"

class battle_for_rokugan::handler::Turn : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int turn     READ turn     NOTIFY turnChanged)
    Q_PROPERTY(int position READ position NOTIFY positionChanged)
public:
    Turn(Stats* stats, QObject* parent);

    void nextTurn();
    void reset(object::PlayerList list);
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
    object::PlayerList m_playerList;
    handler::Stats* m_stats;
    object::Card* m_firstCard;
};

#endif
