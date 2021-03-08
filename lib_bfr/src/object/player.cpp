#include "handler/stats.h"
#include "handler/turn.h"
#include "karta/map.h"
#include "karta/province.h"
#include "karta/territory.h"
#include "object/card.h"
#include "object/clan.h"
#include "object/player.h"
#include "object/secretObjective.h"
#include "token/combat.h"
#include <AfFunction>

BFR::Object::Player::Player(QString name, ClanType clan,
                            Karta::Map* map, Handler::Turn *turns, Handler::Stats* stats,
                            SecretObjective* secret1, SecretObjective* secret2,
                            QObject* parent)
    : QObject(parent),
      m_clan(new Clan(clan, this)),
      m_name(name),
      m_secretObjective1(secret1),
      m_secretObjective2(secret2),
      m_map(map),
      m_stats(stats),
      m_turns(turns),
      m_position(-1),
      m_queue(-1),
      m_startCtrlToken(0)
{
    m_tokenList.push_back(new Token::Combat(this, CombatTokenType::Empty));

    // add all token to start reserve pocket
    addTokenToReserve(CombatTokenType::Army, 6 , 1);
    addTokenToReserve(CombatTokenType::Army, 4 , 2);
    addTokenToReserve(CombatTokenType::Army, 3 , 3);
    addTokenToReserve(CombatTokenType::Army, 2 , 4);
    addTokenToReserve(CombatTokenType::Army, 1 , 5);
    addTokenToReserve(CombatTokenType::Navy, 2 , 1);
    addTokenToReserve(CombatTokenType::Navy, 1 , 2);
    addTokenToReserve(CombatTokenType::Shinobi, 1 , 1);
    addTokenToReserve(CombatTokenType::Shinobi, 2 , 2);
    addTokenToReserve(CombatTokenType::Blessing, 2 , 2);
    addTokenToReserve(CombatTokenType::Diplomacy);
    addTokenToReserve(CombatTokenType::Raid);

    // add special clan turn token
    auto specClanToken = m_clan->uniqueCombatToken();
    addTokenToReserve(specClanToken->type(), 1, specClanToken->value());

    // add base cards
    m_cardList.push_back(new Card(CardType::Shugenja, this));
    m_cardList.push_back(new Card(CardType::Scout, this));
    m_cardList.push_back(new Card(CardType::Scout, this));

    // set turn token control to clan capital
    takeProvince(m_map->operator[](m_clan->homeTerritory())->capital());

    connect(m_turns, &Handler::Turn::turnChanged, this, &Player::updateCombatTokenInAssets);
}

QString BFR::Object::Player::name() const
{
    return m_name;
}

const BFR::Object::Clan* BFR::Object::Player::clan() const
{
    return m_clan;
}

ErrorMsg BFR::Object::Player::pickSecretObjective(SecretObjectiveType secret)
{
    if (this->secretObjective() == nullptr)
        return "Can`t set misssion, it already picked.";

    if (m_secretObjective1->type() == secret)
        m_secretObjective1->setPicked(m_clan);
    else if (m_secretObjective2->type() == secret)
        m_secretObjective2->setPicked(m_clan);
    else
        return "Wrong secret objective, type not found.";

    emit secretObjectivePicked();
    return std::nullopt;
}

unsigned BFR::Object::Player::territoryCardCount() const
{
    unsigned ret = 0;
    for (auto it : m_cardList)
        if (Card::isInitiative(it->type()))
            ret++;
    return ret;
}

unsigned BFR::Object::Player::provinceCount() const
{
    return m_provinceList.size();
}

unsigned BFR::Object::Player::controlTokenCount() const
{
    unsigned ret = provinceCount();
    for (const auto &it : m_provinceList)
        ret += it->controlUp();
    return ret;
}

unsigned BFR::Object::Player::pointsOfHonor() const
{
    unsigned point = secretObjective()->result();
    for (auto reg = TerritoryType::First; reg <= TerritoryType::Last; ++reg){
        auto territory = m_map->operator[](reg);
        if (territory->daimyo() == m_clan->type())
            point += 5;
        for (unsigned i = 0; i < territory->provinceCount(); i++)
            point += territory->operator[](i)->stars();
    }
    return point;
}

int BFR::Object::Player::position() const
{
    return m_position;
}

void BFR::Object::Player::setPosition(int position)
{
    m_position = position;
}

int BFR::Object::Player::queue() const
{
    return m_queue;
}

void BFR::Object::Player::setQueue(int queue)
{
    m_queue = queue;
}

void BFR::Object::Player::takeProvince(Karta::Province* province)
{
    m_provinceList.push_back(province);
    province->setOwner(this);

    if (m_startCtrlToken > 0){
        m_startCtrlToken--;
        emit startCtrlTokenPlaced();
    }

    connect(province, &Karta::Province::ownerChanged,
            this, static_cast<void (Player::*)(Player*)>(&Player::lostProvince));
}

void BFR::Object::Player::lostProvince(Karta::Province* province)
{
    m_provinceList.removeOne(province);
}

void BFR::Object::Player::lostProvince(Player* player)
{
    auto province = qobject_cast <Karta::Province*>(sender());
    if (player != this)
        lostProvince(province);
    disconnect(province, &Karta::Province::ownerChanged,
               this, static_cast<void (Player::*)(Player*)>(&Player::lostProvince));
}

void BFR::Object::Player::untakeProvince(Karta::Province *province)
{
    province->setOwner(nullptr);
}

bool BFR::Object::Player::contains(SOT type) const
{
    return m_secretObjective1->type() == type || m_secretObjective2->type() == type;
}

void BFR::Object::Player::addFirstCard(Card *firstCard)
{
    m_cardList.push_back(firstCard);
}

void BFR::Object::Player::removeFirstCard()
{
    Card* tmp = nullptr;
    for (auto it : m_cardList)
        if (it->type() == CardType::FirstPlayer){
            tmp = it;
            break;
        }
    if (tmp != nullptr)
        m_cardList.removeOne(tmp);
}

void BFR::Object::Player::setStartCtrlToken(int size)
{
    m_startCtrlToken = size;
}

void BattleForRokugan::Object::Player::updateCombatTokenInAssets()
{
    uint needToAdd = m_clan->type() == ClanType::Dragon ? 8 : 6;
    for (auto it : m_tokenList)
        if (it->status() == StatusTokenType::Assets)
            needToAdd--;

    while (needToAdd > 0){
        auto token = m_tokenList[AFfunction::randomInt(0, m_tokenList.count() - 1)];
        if (token->status() == StatusTokenType::Reserve){
            needToAdd--;
            token->setStatus(StatusTokenType::Assets);
        }
    }
    // TODO wait while Dragon get back 2 turn tokens
}

const BFR::Object::SecretObjective* BFR::Object::Player::secretObjective() const
{
    if (m_secretObjective1->picked())
        return m_secretObjective1;

    if (m_secretObjective2->picked())
        return m_secretObjective2;

    return nullptr;
}

void BFR::Object::Player::addTokenToReserve(CombatTokenType type,
                               unsigned char count, unsigned char value)
{
    for (unsigned char i = 0; i < count; i++)
        m_tokenList.push_back(new Token::Combat(this, type, value));
}
