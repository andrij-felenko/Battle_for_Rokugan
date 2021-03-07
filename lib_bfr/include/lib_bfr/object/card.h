#ifndef LIB_BFR_OBJECT_CARD_H
#define LIB_BFR_OBJECT_CARD_H

#include "bfrLib_pre.h"

class BattleForRokugan::Object::Card : public QObject
{
    Q_OBJECT
public:
    Card(CardType type, QObject* parent);
    Q_ENUM(CardType)

    QString name() const;
    QString description() const;
    CardType type() const;

    bool isUsed() const;
    void use();

    static array_u3 randNeutralCard();
    static CardType getNeutralCard(uint i);

    static bool isInitiative(CardType type);
    static bool isTerritory(CardType type);

private:
    CardType m_type;
    bool m_used;

    friend class Handler::Turn;
};

namespace BattleForRokugan {
    CardType operator+ (CardType type, uint i);
    CardType operator+ (CardType card, ClanType clan);
    CardType operator- (CardType left, CardType right);
}

#endif