#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"

bfr::token::Combat::Combat(object::Player *owner, CombatTokenType type, uchar value)
    : QObject(owner), m_value(value), m_owner(owner),m_type(type),
      m_status(type == CTT::Empty ? STT::Assets : STT::Reserve),
      m_blessing(nullptr)
{
    //
}

bfr::token::Combat::Combat(object::Player* owner, CombatTokenType type)
    : Combat(owner, type, 0)
{
    //
}

bfr::CombatTokenType bfr::token::Combat::type() const
{
    return m_type;
}

void bfr::token::Combat::setType(CombatTokenType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

ErrorMsg bfr::token::Combat::name(CombatTokenType type) const
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

ErrorMsg bfr::token::Combat::name() const
{
    return name(m_type);
}

uchar bfr::token::Combat::value() const
{
    if (m_blessing)
        return m_value + m_blessing->value();

    return m_value;
}

void bfr::token::Combat::setValue(uchar value)
{
    if (value == m_value)
        return;
    m_value = value;
}

bool bfr::token::Combat::setBlessing(bfr::token::Combat *token)
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

bfr::object::Player* bfr::token::Combat::owner() const
{
    return m_owner;
}

bfr::StatusTokenType bfr::token::Combat::status() const
{
    return m_status;
}

void bfr::token::Combat::setStatus(const StatusTokenType &status)
{
    m_status = status;
    show(m_status != StatusTokenType::Assets);
}

bfr::token::Combat* bfr::token::Combat::blessing() const
{
    return m_blessing;
}

bool bfr::token::Combat::isShow() const
{
    return m_show;
}

void bfr::token::Combat::show(bool show)
{
    if (m_show == show)
        return;

    m_show = show;
    emit showChanged(m_show);
}
