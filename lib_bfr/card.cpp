#include "lib_bfr/card.h"

BattleForRokugan::Card::Card(const Type type, QObject *parent)
    : QObject(parent), m_type(type)
{
    //
}

QString BattleForRokugan::Card::name() const
{
    switch (m_type) {
    case Type::FirstPlayer:       return tr("First Player");
    case Type::InitiativeCards:   return tr("Initiative cards");
    case Type::LordOfTheLands:    return tr("Lord of the Lands");
    case Type::Reconnaissance:    return tr("Reconnaissance");
    case Type::Shugendja:         return tr("Shugendja");
    case Type::SupremeStrategist: return tr("Supreme Strategist");
    case Type::YoungEmperor:      return tr("Young Emperor");
    default:;
    }
    return "";
}

QString BattleForRokugan::Card::description() const
{
    switch (m_type) {
    case Type::FirstPlayer:
        return tr("(You may play this card at the start of your turn during the Placement Phase.) "
                  "Take any player's battle token from the board. Look at the front of it "
                  "without showing the rest of the players, and then mix the token "
                  "into the owner's personal supply.");

    case Type::LordOfTheLands:
        return tr("The player who controls the most provinces becomes the first player.");

    case Type::Reconnaissance:
        return tr("(You may play this card at the beginning of your turn during the Deployment Phase.) "
                  "Take 1 battle token of any opponent from the board. Look at the front of it, "
                  "without showing the others, and return the token to its place.");

    case Type::Shugendja:
        return tr("(You may play this card at the start of your turn during the Placement Phase.) "
                  "Draw 1 Battle Token from any opponent from the board. "
                  "Open its front side to everyone and send it to the owner's reset.");

    case Type::SupremeStrategist:
        return tr("The player with the most control tokens on the board "
                  "(both face up and down) becomes the first player.");

    case Type::YoungEmperor:
        return tr("The player with the most region cards becomes the first player.");
    default:;
    }
    return "";
}

BattleForRokugan::Card::Type BattleForRokugan::Card::type() const
{
    return m_type;
}
