#ifndef LIB_BFR_PLAYER_H
#define LIB_BFR_PLAYER_H

#include <QtCore/QObject>

namespace BattleForRokugan {
    class Player;
}

class BattleForRokugan::Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject* parent = nullptr);

private:
};

#endif // LIB_BFR_PLAYER_H
