#include "AFbase/AfFunction"
#include "lib_bfr/card.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/clanStats.h"
#include "lib_bfr/game.h"
#include "lib_bfr/map.h"
#include "lib_bfr/mission.h"
#include "lib_bfr/player.h"

BFR::Game::Game(QObject *parent) : QObject(parent)
{
    m_map = new Map(this);
    m_stats = new ClanStats(m_map);
}

BFR::Game::~Game()
{
    clear();
}

void BFR::Game::addPlayer(QString name, ClanType clan)
{
    if (m_playerList.length() >= 5)
        return;

    // add warning why we not add new player
    for (const auto &it : m_playerList)
        if (name == it->name())
            return;

    // make random clan
    while (clan == ClanType::None){
        bool isUnique = true;
        auto clanT = static_cast <ClanType> (AFfunction::randomInt(0, 6));
        for (const auto &it : m_playerList)
            if (clanT == it->clan()->type()){
                isUnique = false;
                break;
            }
        if (isUnique)
            clan = clanT;
    }

    auto it = AFfunction::randomInt(0, m_missionList.size() - 1);
    auto mis_1 = m_missionList.takeAt(it);

    it = AFfunction::randomInt(0, m_missionList.size() - 1);
    auto mis_2 = m_missionList.takeAt(it);

    auto player = new Player(name, clan, m_map, m_stats, mis_1, mis_2, this);
    m_playerList.push_back(player);
    connect(player, &Player::missionSet, this, &Game::isCanStartChanged);
}

void BFR::Game::removePlayer(ClanType clan)
{
    m_playerList.erase(std::remove_if(m_playerList.begin(), m_playerList.end(),
                                      [clan](Player* p){
                           p->deleteLater();
                           return p->clan()->type() == clan;
                       }));
}

void BFR::Game::clear()
{
    // clear all components from game, call only on reinit function
    m_map->clear();
    m_stats->clear();
    m_firstList.clear();

    for (auto it : m_playerList)
        it->deleteLater();
    m_playerList.clear();

    for (auto it : m_cardPocket)
        it->deleteLater();
    m_cardPocket.clear();

    for (auto it : m_missionList)
        it->deleteLater();
    m_missionList.clear();
}

void BFR::Game::init()
{
    // create all pregame component
    m_turn = 0;
    m_phase = Phase::Pregame;

    // init cardPocket
    m_cardPocket.clear();
    m_cardPocket.push_back(new Card(CardType::FirstPlayer, this));
    for (int i = 0; i < 11; i++){
        auto cardType = CardType::FirstRegion + i * 2 + AFfunction::randomInt(0, 1);
        m_cardPocket.push_back(new Card(cardType, this));
    }
    for (int i = 0; i < 12; i++)
        m_missionList.push_back(new Mission(static_cast <MissionType>(i), m_map, m_stats, this));
}

bool BFR::Game::checkIsCanStart()
{
    /// check pregame component, if smth not fill full
    /// return value (emit) need for button start battle in interface
    // check count of players, must be more or equal 2
    if (m_playerList.count() < 2){
        // TODO add warning msg
        // "Player not enought, need at least 2 player"
        return false;
    }

    // check mission, every player must have one
    for (auto it : m_playerList)
        if (it->mission() == nullptr){
            // TODO add error msg
//            "Mission of player " + it->name() + " not found."
            return false;
        }

    return true;
}

void BFR::Game::reinit()
{
    clear();
    init();
}

ErrorMsg BFR::Game::start()
{
    // just set main provinces in capital, set first player for first turn
    //


    // make random first turn card
    m_firstList.clear();
    auto neutralCard = Card::randNeutralCard();
    for (unsigned i = 0 ; i < 5 - m_playerList.length(); i++)
        m_firstList.insert(AFlib::Function::randomInt(0, m_firstList.size()),
                           Card::getNeutralCard(neutralCard[i]));
    for (auto it : m_playerList)
        m_firstList.insert(AFfunction::randomInt(0, m_firstList.size()),
                           CardType::FirstInitiative + it->clan()->type());

    // TODO choose mission to all players
    // TODO set control token to capital
    // TODO set n control token but each person (only first step)
    // TODO step by step put control token to map

    //#Turn
    // choose first player
    updatePlayerPosition();

    // TODO add turn token to 6 (8 if dragon)
    // TODO wait while Dragon get back 2 turn tokens

    if (m_turn > 1){
        // TODO add region card to player
        // TODO use region card
    }
    // TODO set turn token on map and (if player want) use region shadow card or player card

    // #Turn-battle phase
    // TODO rollback turn token
    // TODO burn all
    // TODO use not battle token
    // TODO battle
    // TODO call next turn

    return std::nullopt;
}

BFR::ClanType BFR::Game::getCurrentFirstPlayer()
{
    ClanType clan = ClanType::None;
    CardType card;
    for (auto it : m_firstList){
        switch (it) {
        case CardType::InitiativeCrab:
        case CardType::InitiativeCrane:
        case CardType::InitiativeDragon:
        case CardType::InitiativeLion:
        case CardType::InitiativePhoenix:
        case CardType::InitiativeScorpion:
        case CardType::InitiativeUnicorn:
            clan = static_cast <ClanType>(it - CardType::FirstInitiative); break;
        case CardType::LordOfTheLands: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement <uint, 7> (getClanProvinceOwned()).first;
            clan = static_cast <ClanType>(clanIndex);
            break;
        }
        case CardType::SupremeStrategist: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement <uint, 7> (getClanControlToken()).first;
            clan = static_cast <ClanType>(clanIndex);
            break;
        }
        case CardType::YoungEmperor: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement <uint, 7> (getRegionCardOwner()).first;
            clan = static_cast <ClanType>(clanIndex);
            break;
        }
        default: return ClanType::None;
        }

        card = it;
    }

    // remove taked first from list
    m_firstList.removeOne(card);
    return clan;
}

void BFR::Game::updatePlayerPosition()
{
    typedef std::pair <ClanType, unsigned int> PointClan;
    std::vector <PointClan> points;
    for (auto it : m_playerList)
        points.push_back(std::make_pair(it->clan()->type(), it->pointsOfHonor()));

    // TODO add some other additional checked
    // sort points clan vector
    for (uint i = 0; i < points.size(); i++){
        uint minIndex = i;
        uint minValue = points[i].second;

        for (uint j = i + 1; j < points.size(); j++)
            if (points[j].second > minValue){
                minIndex = j;
                minValue = points[j].second;
            }

        if (minIndex != i)
            std::swap(points[i], points[minIndex]);
    }

    // set position to Player object
    for (auto it : m_playerList){
        int position = 0;
        for (auto p = points.begin(); p != points.end(); ++p, ++position)
            if (p->first == it->clan()->type()){
                it->setPosition(position);
                break;
            }
    }
}

void BFR::Game::updateTurnQueue()
{
    for (auto it : m_playerList)
        it->setPosition(-1);

    bool isFound = false;
    int currentPosition = 0;
    ClanType firstClan = getCurrentFirstPlayer();
    for (auto it : m_playerList){
        if (it->clan()->type() == firstClan)
            isFound = true;

        if (isFound){
            it->setPosition(currentPosition);
            currentPosition++;
        }
    }

    for (auto it : m_playerList){
        if (it->clan()->type() == firstClan)
            break;

        it->setPosition(currentPosition);
        currentPosition++;
    }
}

array_u7 BFR::Game::getClanControlToken() const
{
    array_u7 ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <uint>(it->clan()->type())] = it->controlTokenCount();
    return ret;
}

array_u7 BFR::Game::getClanProvinceOwned() const
{
    array_u7 ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <uint>(it->clan()->type())] = it->provinceCount();
    return ret;
}

array_u7 BFR::Game::getRegionCardOwner() const
{
    array_u7 ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <uint>(it->clan()->type())] = it->regionCardCount();
    return ret;
}
