#ifndef LIB_BFR_CARD_H
#define LIB_BFR_CARD_H

#include <QtCore/QObject>

namespace BattleForRokugan {
    class Card;
}

class BattleForRokugan::Card : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        FirstPlayer,       ///< [1]
        Shugendja,         ///< [5]
        InitiativeCards,   ///< [7 for each nation with their logit and 3 neutral cards]
        LordOfTheLands,    ///< Neutral card
        SupremeStrategist, ///< Neutral card
        YoungEmperor,      ///< Neutral card
        Reconnaissance     ///< [10]
    }; Q_ENUM(Type)

    Card(const Type type, QObject* parent = nullptr);

    QString name() const;
    QString description() const;
    Type type() const;

private:
    Type m_type;
};

#endif // LIB_BFR_CARD_H
