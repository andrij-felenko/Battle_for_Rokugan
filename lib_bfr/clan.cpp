#include "lib_bfr/clan.h"
#include "lib_bfr/player.h"
#include "lib_bfr/turnToken.h"

BattleForRokugan::Clan::Clan(ClanType type, QObject *parent)
    : QObject(parent), m_type(type), m_specialToken(nullptr)
{
    auto player = qobject_cast <Player*> (parent);
    typedef TurnTokenType TTT;
    switch (m_type) {
    case ClanType::Crane:    m_specialToken = new TurnToken(player, TTT::Diplomacy);
    case ClanType::Unicorn:  m_specialToken = new TurnToken(player, TTT::Sabotage);
    case ClanType::Crab:     m_specialToken = new TurnToken(player, TTT::Navy,     3);
    case ClanType::Dragon:
    case ClanType::Phoenix:  m_specialToken = new TurnToken(player, TTT::Blessing, 3);
    case ClanType::Scorpion: m_specialToken = new TurnToken(player, TTT::Shinobi,  3);
    case ClanType::Lion:     m_specialToken = new TurnToken(player, TTT::Army,     6);
    default:;
    }
}

BFR::RegionType BFR::Clan::homeRegion() const { return homeRegion(m_type);}
BFR::ClanType   BFR::Clan::type()       const { return            m_type ;}
QString         BFR::Clan::name()       const { return       name(m_type);}

void BFR::Clan::setType(ClanType type)
{
    m_type = type;
}

BFR::RegionType BFR::Clan::homeRegion(ClanType type)
{
    switch (type) {
    case ClanType::Crab:     return RegionType::Crab;
    case ClanType::Crane:    return RegionType::Crane;
    case ClanType::Dragon:   return RegionType::Dragon;
    case ClanType::Lion:     return RegionType::Lion;
    case ClanType::Phoenix:  return RegionType::Phoenix;
    case ClanType::Scorpion: return RegionType::Scorpion;
    case ClanType::Unicorn:  return RegionType::Unicorn;
    default:;
    }
    return RegionType::None;
}

const BFR::TurnToken* BFR::Clan::specialClanToken() const
{
    return m_specialToken;
}

QString BFR::Clan::name(ClanType type)
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

namespace BattleForRokugan {
    ClanType operator+(ClanType type, uint i)
    {
        uint value = static_cast <uint> (type) + i;
        return static_cast <ClanType> (value);
    }
}
