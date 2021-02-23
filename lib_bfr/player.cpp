#include "lib_bfr/card.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/clanStats.h"
#include "lib_bfr/map.h"
#include "lib_bfr/mission.h"
#include "lib_bfr/player.h"
#include "lib_bfr/province.h"
#include "lib_bfr/region.h"
#include "lib_bfr/turnToken.h"

BFR::Player::Player(QString name, ClanType clan, Map* map, ClanStats* stats,
                    Mission* mis1, Mission* mis2, QObject* parent)
    : QObject(parent),
      m_clan(new Clan(clan, this)),
      m_name(name),
      m_mission1(mis1),
      m_mission2(mis2),
      m_map(map),
      m_stats(stats),
      m_position(-1),
      m_queue(-1)
{
    m_tokenAssetsList.push_back(new TurnToken(TurnTokenType::Empty, this));

    // add all token to start reserve pocket
    addTokenToReserve(TurnTokenType::Army, 6 , 1);
    addTokenToReserve(TurnTokenType::Army, 4 , 2);
    addTokenToReserve(TurnTokenType::Army, 3 , 3);
    addTokenToReserve(TurnTokenType::Army, 2 , 4);
    addTokenToReserve(TurnTokenType::Army, 1 , 5);
    addTokenToReserve(TurnTokenType::Navy, 2 , 1);
    addTokenToReserve(TurnTokenType::Navy, 1 , 2);
    addTokenToReserve(TurnTokenType::Shinobi, 1 , 1);
    addTokenToReserve(TurnTokenType::Shinobi, 2 , 2);
    addTokenToReserve(TurnTokenType::Blessing, 2 , 2);
    addTokenToReserve(TurnTokenType::Diplomacy);
    addTokenToReserve(TurnTokenType::Sabotage);

    // add special clan turn token
    auto specClanToken = m_clan->specialClanToken();
    addTokenToReserve(specClanToken->type(), 1, specClanToken->value());

    // add base cards
    m_cardList.push_back(new Card(CardType::Shugendja, this));
    m_cardList.push_back(new Card(CardType::Intelligence, this));
    m_cardList.push_back(new Card(CardType::Intelligence, this));
}

BattleForRokugan::Player::~Player()
{
    // TODO
}

QString BFR::Player::name() const
{
    return m_name;
}

const BFR::Clan* BFR::Player::clan() const
{
    return m_clan;
}

ErrorMsg BFR::Player::pickMission(MissionType mission)
{
    if (this->mission() == nullptr)
        return "Can`t set misssion, it already picked.";

    if (m_mission1->type() == mission)
        m_mission1->setPicked(m_clan);
    else if (m_mission2->type() == mission)
        m_mission2->setPicked(m_clan);
    else
        return "Wrong mission, type not found.";

    return std::nullopt;
}

unsigned BFR::Player::regionCardCount() const
{
    unsigned ret = 0;
    for (auto it : m_cardList)
        if (Card::isInitiative(it->type()))
            ret++;
    return ret;
}

unsigned BFR::Player::provinceCount() const
{
    return m_provinceList.size();
}

unsigned BFR::Player::controlTokenCount() const
{
    unsigned ret = provinceCount();
    for (const auto &it : m_provinceList)
        ret += it->controlUp();
    return ret;
}

unsigned BFR::Player::pointsOfHonor() const
{
    unsigned point = mission()->result();
    for (auto reg = RegionType::First; reg != RegionType::Last; ++reg){
        auto region = m_map->operator[](reg);
        if (region->daimyo() == m_clan->type())
            point += 5;
        for (unsigned i = 0; i < region->provinceCount(); i++)
            point += region->operator[](i)->stars();
    }
    return point;
}

int BFR::Player::position() const
{
    return m_position;
}

void BFR::Player::setPosition(int position)
{
    m_position = position;
}

int BFR::Player::queue() const
{
    return m_queue;
}

void BFR::Player::setQueue(int queue)
{
    m_queue = queue;
}

void BFR::Player::takeProvince(Province* province)
{
//    province->setClanOwner(m_clan->type());
    // TODO
}

void BFR::Player::lostProvince(Province* province)
{
    // TODO
}

bool BFR::Player::contains(MissionType type) const
{
    return m_mission1->type() == type || m_mission2->type() == type;
}

const BFR::Mission* BFR::Player::mission() const
{
    if (m_mission1->picked())
        return m_mission1;

    if (m_mission2->picked())
        return m_mission2;

    return nullptr;
}

void BFR::Player::addTokenToReserve(TurnTokenType type,
                               unsigned char count, unsigned char value)
{
    for (unsigned char i = 0; i < count; i++)
        m_tokenReserveList.push_back(new TurnToken(type, value, this));
}
