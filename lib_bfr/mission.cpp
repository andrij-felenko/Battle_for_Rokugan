#include "lib_bfr/mission.h"

BattleForRokugan::Mission::Mission(QObject *parent)
    : QObject(parent)
{
    //
}

QString BattleForRokugan::Mission::description(const BattleForRokugan::Mission::Type &type)
{
    switch (type) {
    case Type::Battlefield:
        return tr("If you control a Lion Clan Capital Province or 2 provinces "
                  "in a Lion Clan Region at the end of the game, gain 7 Honor Points.");

    case Type::EmeraldEmpire:
        return tr("If at the end of the game you control a chain of 6 contiguous provinces "
                  "that belong to 3 different regions, you will receive 10 honor points.");

    case Type::EmpireRiceBowl:
        return tr("If at the end you control a Capital Province of the Crane Clan "
                  "or 2 provinces in the Crane Region, gain 6 Honor Points.");

    case Type::ForgottenLands:
        return tr("If you control the Shadowlands (both provinces) "
                  "at the end of the game, gain 3 honor points.");

    case Type::GreatLibrary:
        return tr("If at the end you control a Phoenix capital province or 2 provinces "
                  "in a Phoenix clan region, gain 7 honor points.");

    case Type::GreatWallOfTheNorth:
        return tr("If at the end of the game you control a Dragon clan capital province "
                  "or 2 provinces in a Dragon clan region, gain 6 honor points.");

    case Type::MasterOfTheSeas:
        return tr("If you control 6 coastal provinces at the end of the game, "
                  "gain 10 honor points.");

    case Type::Modesty_PolitenessOfKings:
        return tr("If you control the least number of provinces at the end of the game, "
                  "you will receive 10 honor points. If there is a tie, "
                  "you still complete this goal and earn honor points.");

    case Type::UbiquitousInfluence:
        return tr("If you control at least one province in 7 different regions "
                  "at the end of the game, you will receive 10 Honor points.");

    case Type::SuburbOfTheFiveWinds:
        return tr("If at the end of the game you control a Unicorn capital province "
                  "or 2 provinces in a Unicorn clan region, gain 6 honor points.");

    case Type::TheLastLineOfDefense:
        return tr("If at the end of the game you control a Crab capital province "
                  "or 2 provinces in the Crab clan regions, gain 5 honor points.");

    case Type::VaultOfSecrets:
        return tr("If at the end of the game you control a Scorpion capital province "
                  "or 2 provinces in a Scorpio clan region, gain 7 honor points.");
    default:;
    }
    return "";
}
