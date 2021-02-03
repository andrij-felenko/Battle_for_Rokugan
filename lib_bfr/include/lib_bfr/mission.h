#ifndef LIB_BFR_MISSION_H
#define LIB_BFR_MISSION_H

#include <QtCore/QObject>

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

    Mission(QObject* parent = nullptr);

    QString description(const Type& type);

private:
};

#endif // LIB_BFR_MISSION_H
