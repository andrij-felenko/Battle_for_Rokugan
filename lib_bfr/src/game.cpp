#include "AFbase/AfFunction"
#include "lib_bfr/game.h"
#include "lib_bfr/handler/battle.h"
#include "lib_bfr/handler/stats.h"
#include "lib_bfr/handler/turn.h"
#include "lib_bfr/karta/map.h"
#include "lib_bfr/object/card.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/object/secretObjective.h"

bfr::Game::Game(QObject *parent) : QObject(parent)
{
    m_map = new karta::Map(this);
    m_battle = new handler::Battle(m_map, this);
    m_stats = new handler::Stats(m_map);
    m_turns = new handler::Turn(m_stats, this);

    connect(m_map, &karta::Map::allTokenOpened, m_battle, &handler::Battle::run);
    connect(m_turns, &handler::Turn::turnChanged,        m_map, &karta::Map::newTurn);
    connect(m_turns, &handler::Turn::turnPlacedFinished, m_map, &karta::Map::openTokens);
    connect(m_battle, &handler::Battle::battleFinished, m_stats, &handler::Stats::update);
    connect(m_battle, &handler::Battle::battleFinished, m_turns, &handler::Turn::nextTurn);
}

bfr::Game::~Game()
{
    clear();
    for (const auto &it : m_cardPocket)
        if (it->parent() == nullptr)
            it->deleteLater();
}

void bfr::Game::addPlayer(QString name, ClanType clan)
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

    auto it = AFfunction::randomInt(0, m_secretObjectiveList.size() - 1);
    auto so_1 = m_secretObjectiveList.takeAt(it);

    it = AFfunction::randomInt(0, m_secretObjectiveList.size() - 1);
    auto so_2 = m_secretObjectiveList.takeAt(it);

    auto player = new object::Player(name, clan, m_map, m_turns, m_stats, so_1, so_2, this);
    m_playerList.push_back(player);
    connect(player, &object::Player::secretObjectivePicked, this, &Game::checkIsCanStart);
    checkIsCanStart();
}

void bfr::Game::removePlayer(ClanType clan)
{
    m_playerList.erase(std::remove_if(m_playerList.begin(), m_playerList.end(),
                                      [clan](object::Player* p){
                           p->deleteLater();
                           return p->clan()->type() == clan;
                       }));
}

void bfr::Game::clear()
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

    for (auto it : m_secretObjectiveList)
        it->deleteLater();
    m_secretObjectiveList.clear();
}

void bfr::Game::init()
{
    // init cardPocket
    m_cardPocket.clear();
    for (int i = 0; i < 11; i++){
        auto cardType = CardType::FirstTerritory + i * 2 + AFfunction::randomInt(0, 1);
        m_cardPocket.push_back(new object::Card(cardType));
    }
    for (int i = 0; i < 12; i++){
        auto so = new object::SecretObjective(static_cast <SecretObjectiveType>(i),
                                              m_map, m_stats, this);
        m_secretObjectiveList.push_back(so);
    }
}

bool bfr::Game::checkIsCanStart()
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

    // check secret objective, every player must have one
    for (auto it : m_playerList)
        if (it->secretObjective() == nullptr){
            // TODO add error msg
//            "Secret objective of player " + it->name() + " not found."
            emit isCanStartChanged(false);
            return false;
        }

    emit isCanStartChanged(true);
    return true;
}

void bfr::Game::reinit()
{
    clear();
    init();
}

void bfr::Game::start()
{
    m_battle->reset(m_playerList);
    m_turns->reset(m_playerList);

//    if (m_turn > 1){
        // TODO add territory card to player
        // TODO use territory card
//    }
    // TODO set turn token on map and (if player want) use territory shadow card or player card
}
