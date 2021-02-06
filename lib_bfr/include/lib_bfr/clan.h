#ifndef LIB_BFR_CLAN_H
#define LIB_BFR_CLAN_H

#include <QtCore/QObject>

namespace BattleForRokugan {
    class Clan;
    class TurnToken;
}

class BattleForRokugan::Clan : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Crab,
        Crane,
        Dragon,
        Lion,
        Phoenix,
        Scorpion,
        Unicorn,
        None,
        First = Crab
    }; Q_ENUM(Type)

    Clan(const Type& type, QObject* parent = nullptr);

    Type type() const;
    void setType(const Type &type);

    static QString name(const Type& type);
    QString name() const;

    TurnToken specialClanToken() const;

private:
    Type m_type;
};

BattleForRokugan::Clan::Type operator+(BattleForRokugan::Clan::Type type, unsigned i);

#endif // LIB_BFR_CLAN_H
