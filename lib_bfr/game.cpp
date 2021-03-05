#include "AFbase/AfFunction"
#include "lib_bfr/battle.h"
#include "lib_bfr/card.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/clanStats.h"
#include "lib_bfr/game.h"
#include "lib_bfr/map.h"
#include "lib_bfr/mission.h"
#include "lib_bfr/player.h"
#include "lib_bfr/turnManager.h"

BFR::Game::Game(QObject *parent) : QObject(parent)
{
    m_map = new Map(this);
    m_battle = new Battle(m_map, this);
    m_stats = new ClanStats(m_map);
    m_turns = new TurnManager(m_stats, this);

    connect(m_map, &Map::allTokenOpened, m_battle, &Battle::run);
    connect(m_turns, &TurnManager::turnPlacedFinished, m_map, &Map::openTokens);
    connect(m_battle, &Battle::battleFinished, m_turns, &TurnManager::nextTurn);
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
    connect(player, &Player::missionPicked, this, &Game::checkIsCanStart);
    checkIsCanStart();
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
    m_turns->clear();

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
        emit isCanStartChanged(false);
        return false;
    }

    // check mission, every player must have one
    for (auto it : m_playerList)
        if (it->mission() == nullptr){
            // TODO add error msg
//            "Mission of player " + it->name() + " not found."
            emit isCanStartChanged(false);
            return false;
        }

    emit isCanStartChanged(true);
    return true;
}

void BFR::Game::reinit()
{
    clear();
    init();
}

void BFR::Game::start()
{
    m_battle->reset(m_playerList);
    m_turns->reset(m_playerList);

    // TODO choose mission to all players
    // TODO set control token to capital
    // TODO set n control token but each person (only first step)
    // TODO step by step put control token to map

    //#Turn
    // choose first player

    // TODO add turn token to 6 (8 if dragon)
    // TODO wait while Dragon get back 2 turn tokens

//    if (m_turn > 1){
        // TODO add region card to player
        // TODO use region card
//    }
    // TODO set turn token on map and (if player want) use region shadow card or player card

    // #Turn-battle phase
    // TODO rollback turn token
    // TODO burn all
    // TODO use not battle token
    // TODO battle
    // TODO call next turn
}
