#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"

BFR::Token::Combat::Combat(Object::Player *owner, CombatTokenType type, uchar value)
    : QObject(owner), m_value(value), m_owner(owner),m_type(type),
      m_status(type == CTT::Empty ? STT::Assets : STT::Reserve),
      m_blessing(nullptr)
{
    //
}

BFR::Token::Combat::Combat(Object::Player* owner, CombatTokenType type)
    : Combat(owner, type, 0)
{
    //
}

BFR::CombatTokenType BFR::Token::Combat::type() const
{
    return m_type;
}

void BFR::Token::Combat::setType(CombatTokenType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

ErrorMsg BFR::Token::Combat::name(CombatTokenType type) const
{
    switch (type) {
    case CombatTokenType::Army:      return tr("Army");
    case CombatTokenType::Blessing:  return tr("Blessing");
    case CombatTokenType::Diplomacy: return tr("Diplomacy");
    case CombatTokenType::Empty:     return tr("Empty");
    case CombatTokenType::Navy:      return tr("Navy");
    case CombatTokenType::Raid:      return tr("Raid");
    case CombatTokenType::Shinobi:   return tr("Shinobi");
    default:;
    }
    return std::nullopt;
}

ErrorMsg BFR::Token::Combat::name() const
{
    return name(m_type);
}

uchar BFR::Token::Combat::value() const
{
    if (m_blessing)
        return m_value + m_blessing->value();

    return m_value;
}

void BFR::Token::Combat::setValue(uchar value)
{
    if (value == m_value)
        return;
    m_value = value;
}

bool BFR::Token::Combat::setBlessing(BFR::Token::Combat *token)
{
    if (m_blessing)
        return false;

    switch (m_type) {
    case CombatTokenType::Army:
    case CombatTokenType::Navy:
    case CombatTokenType::Shinobi: m_blessing = token; return true;
    default:;
    }
    return false;
}

BFR::Object::Player* BattleForRokugan::Token::Combat::owner() const
{
    return m_owner;
}

BFR::StatusTokenType BFR::Token::Combat::status() const
{
    return m_status;
}

void BFR::Token::Combat::setStatus(const StatusTokenType &status)
{
    m_status = status;
}

BFR::Token::Combat* BFR::Token::Combat::blessing() const
{
    return m_blessing;
}
