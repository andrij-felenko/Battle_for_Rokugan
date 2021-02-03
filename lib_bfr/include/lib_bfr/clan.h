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
        Crane,
        Dragon,
        Phoenix,
        Scorpion,
        Lion,
        Crab,
        Unicorn,
        None
    }; Q_ENUM(Type)

    Clan(const Type& type, QObject* parent = nullptr);

    Type type() const;
    void setType(const Type &type);

    QString name(const Type& type);

    TurnToken specialClanToken(const Type type) const;

private:
    Type m_type;
};

#endif // LIB_BFR_CLAN_H
