#include "lib_bfr/turnToken.h"

BFR::TurnToken::TurnToken(TurnTokenType type, uchar value, QObject *parent)
    : QObject(parent), m_type(type), m_value(value)
{
    //
}

BFR::TurnToken::TurnToken(TurnTokenType type, QObject *parent)
    : TurnToken(type, 0, parent)
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
    return m_value;
}

void BFR::TurnToken::setValue(uchar value)
{
    if (value == m_value)
        return;
    m_value = value;
}
