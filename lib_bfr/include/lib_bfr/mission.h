#ifndef LIB_BFR_MISSION_H
#define LIB_BFR_MISSION_H

#include <QtCore/QObject>
#include "gameMap.h"

namespace BattleForRokugan {
    class Mission;
}

class BattleForRokugan::Mission : public QObject
{
    Q_OBJECT
public:
    enum class Type : unsigned char {
        SuburbOfTheFiveWinds,
        GreatLibrary,
        VaultOfSecrets,
        EmpireRiceBowl,
        GreatWallOfTheNorth,
        MasterOfTheSeas,
        EmeraldEmpire,
        Modesty_PolitenessOfKings,
        UbiquitousInfluence,
        Battlefield,
        TheLastLineOfDefense,
        ForgottenLands
    }; Q_ENUM(Type)

    Mission(const Type& type, QObject* parent = nullptr);

    QString name();
    QString description();

    int result(Clan::Type clan, const GameMap* const map) const;
    static int result(Type type, Clan::Type clan, const GameMap* const map);

    QString name() const;
    static QString name(const Type& type);

    QString description() const;
    static QString description(const Type& type);

private:
    Type m_type;
};

#endif // LIB_BFR_MISSION_H
