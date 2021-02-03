#include "lib_bfr/turnToken.h"

BattleForRokugan::TurnToken::TurnToken(const BattleForRokugan::TurnToken::Type &type, unsigned char value)
    : m_type(type), m_value(value)
{
    //
}

BattleForRokugan::TurnToken::Type BattleForRokugan::TurnToken::type() const
{
    return m_type;
}

void BattleForRokugan::TurnToken::setType(const BattleForRokugan::TurnToken::Type &type)
{
    if (type == m_type)
        return;
    m_type = type;
}

std::optional <QString> BattleForRokugan::TurnToken::name(const BattleForRokugan::TurnToken::Type &type) const
{
    switch (type) {
    case Type::Army:      return tr("Army");
    case Type::Blessing:  return tr("Blessing");
    case Type::Diplomacy: return tr("Diplomacy");
    case Type::Empty:     return tr("Empty");
    case Type::Navy:      return tr("Navy");
    case Type::Sabotage:  return tr("Sabotage");
    case Type::Shinobi:   return tr("Shinobi");
    default:;
    }
    return std::nullopt;
}

std::optional <QString> BattleForRokugan::TurnToken::name() const
{
    return name(m_type);
}

unsigned char BattleForRokugan::TurnToken::value() const
{
    return m_value;
}

void BattleForRokugan::TurnToken::setValue(unsigned char value)
{
    if (value == m_value)
        return;
    m_value = value;
}
