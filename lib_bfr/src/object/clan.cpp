#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"

bfr::object::Clan::Clan(ClanType type, QObject *parent)
    : QObject(parent), m_type(type), m_specialToken(nullptr)
{
    auto player = qobject_cast <Player*> (parent);
    typedef CombatTokenType TTT;
    switch (m_type) {
    case ClanType::Crane:    m_specialToken = new token::Combat(player, TTT::Diplomacy);
    case ClanType::Unicorn:  m_specialToken = new token::Combat(player, TTT::Raid);
    case ClanType::Crab:     m_specialToken = new token::Combat(player, TTT::Navy,     3);
    case ClanType::Dragon:
    case ClanType::Phoenix:  m_specialToken = new token::Combat(player, TTT::Blessing, 3);
    case ClanType::Scorpion: m_specialToken = new token::Combat(player, TTT::Shinobi,  3);
    case ClanType::Lion:     m_specialToken = new token::Combat(player, TTT::Army,     6);
    default:;
    }
}

bfr::TerritoryType bfr::object::Clan::homeTerritory() const { return homeTerritory(m_type);}
bfr::ClanType      bfr::object::Clan::type()          const { return               m_type ;}
QString            bfr::object::Clan::name()          const { return          name(m_type);}

void bfr::object::Clan::setType(ClanType type)
{
    m_type = type;
}

bfr::TerritoryType bfr::object::Clan::homeTerritory(ClanType type)
{
    switch (type) {
    case ClanType::Crab:     return TerritoryType::Crab;
    case ClanType::Crane:    return TerritoryType::Crane;
    case ClanType::Dragon:   return TerritoryType::Dragon;
    case ClanType::Lion:     return TerritoryType::Lion;
    case ClanType::Phoenix:  return TerritoryType::Phoenix;
    case ClanType::Scorpion: return TerritoryType::Scorpion;
    case ClanType::Unicorn:  return TerritoryType::Unicorn;
    default:;
    }
    return TerritoryType::None;
}

const bfr::token::Combat* bfr::object::Clan::uniqueCombatToken() const
{
    return m_specialToken;
}

QString bfr::object::Clan::name(ClanType type)
{
    switch (type) {
    case ClanType::Crab:     return tr("Crab clan");
    case ClanType::Crane:    return tr("Crane clan");
    case ClanType::Dragon:   return tr("Dragon clan");
    case ClanType::Lion:     return tr("Lion clan");
    case ClanType::Phoenix:  return tr("Phoenix clan");
    case ClanType::Scorpion: return tr("Scorpion clan");
    case ClanType::Unicorn:  return tr("Unicorn clan");
    default:;
    }
    return tr("No one");
}

namespace battle_for_rokugan {
    ClanType operator+(ClanType type, uint i)
    {
        uint value = static_cast <uint> (type) + i;
        return static_cast <ClanType> (value);
    }
}
