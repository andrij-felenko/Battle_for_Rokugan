#include "lib_bfr/clan.h"
#include "lib_bfr/turnToken.h"

BattleForRokugan::Clan::Clan(const Type& type, QObject *parent)
    : QObject(parent), m_type(type)
{
    //
}

BattleForRokugan::Clan::Type BattleForRokugan::Clan::type() const
{
    return m_type;
}

void BattleForRokugan::Clan::setType(const Type &type)
{
    m_type = type;
}

QString BattleForRokugan::Clan::name(const BattleForRokugan::Clan::Type &type)
{
    switch (type) {
    case Type::Crab:     return tr("Crab clan");
    case Type::Crane:    return tr("Crane clan");
    case Type::Dragon:   return tr("Dragon clan");
    case Type::Lion:     return tr("Lion clan");
    case Type::Phoenix:  return tr("Phoenix clan");
    case Type::Scorpion: return tr("Scorpion clan");
    case Type::Unicorn:  return tr("Unicorn clan");
    default:;
    }
    return tr("No one");
}

QString BattleForRokugan::Clan::name() const
{
    return name(m_type);
}

BattleForRokugan::TurnToken BattleForRokugan::Clan::specialClanToken() const
{
    switch (m_type) {
    case Type::Crane:    return TurnToken(TurnToken::Type::Diplomacy);
    case Type::Unicorn:  return TurnToken(TurnToken::Type::Sabotage);
    case Type::Crab:     return TurnToken(TurnToken::Type::Navy,     3);
    case Type::Dragon:   return TurnToken(TurnToken::Type::Blessing, 3);
    case Type::Phoenix:  return TurnToken(TurnToken::Type::Blessing, 3);
    case Type::Scorpion: return TurnToken(TurnToken::Type::Shinobi,  3);
    case Type::Lion:     return TurnToken(TurnToken::Type::Army,     6);
    default:;
    }
    return TurnToken(TurnToken::Type::None);
}

BattleForRokugan::Clan::Type operator+(BattleForRokugan::Clan::Type type, unsigned i)
{
    using namespace BattleForRokugan;
    return static_cast <Clan::Type>(static_cast <unsigned>(type) + i);
}
