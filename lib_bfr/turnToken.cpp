#include "lib_bfr/player.h"
#include "lib_bfr/turnToken.h"

BFR::TurnToken::TurnToken(Player *owner, TurnTokenType type, uchar value)
    : QObject(owner), m_value(value), m_owner(owner),m_type(type),
      m_status(type == TTT::Empty ? TTS::Assets : TTS::Reserve),
      m_blessing(nullptr)
{
    //
}

BFR::TurnToken::TurnToken(Player* owner, TurnTokenType type)
    : TurnToken(owner, type, 0)
{
    //
}

BFR::TurnTokenType BFR::TurnToken::type() const
{
    return m_type;
}

void BFR::TurnToken::setType(TurnTokenType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

ErrorMsg BFR::TurnToken::name(TurnTokenType type) const
{
    switch (type) {
    case TurnTokenType::Army:      return tr("Army");
    case TurnTokenType::Blessing:  return tr("Blessing");
    case TurnTokenType::Diplomacy: return tr("Diplomacy");
    case TurnTokenType::Empty:     return tr("Empty");
    case TurnTokenType::Navy:      return tr("Navy");
    case TurnTokenType::Sabotage:  return tr("Sabotage");
    case TurnTokenType::Shinobi:   return tr("Shinobi");
    default:;
    }
    return std::nullopt;
}

ErrorMsg BFR::TurnToken::name() const
{
    return name(m_type);
}

uchar BFR::TurnToken::value() const
{
    if (m_blessing)
        return m_value + m_blessing->value();

    return m_value;
}

void BFR::TurnToken::setValue(uchar value)
{
    if (value == m_value)
        return;
    m_value = value;
}

bool BattleForRokugan::TurnToken::setBlessing(BattleForRokugan::TurnToken *token)
{
    if (m_blessing)
        return false;

    switch (m_type) {
    case TurnTokenType::Army:
    case TurnTokenType::Navy:
    case TurnTokenType::Shinobi: m_blessing = token; return true;
    default:;
    }
    return false;
}

BFR::Player *BattleForRokugan::TurnToken::owner() const
{
    return m_owner;
}

BFR::TurnTokenStatus BFR::TurnToken::status() const
{
    return m_status;
}

void BFR::TurnToken::setStatus(const TurnTokenStatus &status)
{
    m_status = status;
}

BFR::TurnToken* BFR::TurnToken::blessing() const
{
    return m_blessing;
}
