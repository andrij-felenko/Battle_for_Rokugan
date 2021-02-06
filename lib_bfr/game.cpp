#include "lib_bfr/game.h"
#include <QDebug>
#include "AFbase/AfFunction"

BattleForRokugan::Game::Game(QObject *parent) : QObject(parent)
{
    //
}

void BattleForRokugan::Game::addPlayer(QString name, BattleForRokugan::Clan::Type clan)
{
    if (m_playerList.length() >= 5)
        return;

    // add warning why we not add new player
    for (auto it : m_playerList)
        if (name == it->name())
            return;

    // make random clan
    while (clan == Clan::Type::None){
        bool isUnique = true;
        auto clanT = static_cast <Clan::Type> (AFlib::Function::randomInt(0, 6));
        for (auto it : m_playerList)
            if (clanT == it->clan()->type()){
                isUnique = false;
                break;
            }
        if (isUnique)
            clan = clanT;
    }

    m_playerList.push_back(new Player(name, clan, this));
}

void BattleForRokugan::Game::removePlayer(const BattleForRokugan::Clan::Type& clan)
{
    m_playerList.erase(std::remove_if(m_playerList.begin(), m_playerList.end(),
                                      [clan](Player* p){ return p->clan()->type() == clan; }));
}

std::optional <QString> BattleForRokugan::Game::start()
{
    if (m_playerList.length() < 2)
        return "Player not enought, need at least 2 player";

    //#Pregame
    m_turn = -1;
    m_phase = Phase::Pregame;
    // call Pregame status
    // init cardPocket
    m_cardPocket.clear();
    m_cardPocket.push_back(new Card(Card::Type::FirstPlayer, this));
    for (int i = 0; i < 11; i++){
        auto cardType = Card::Type::FirstRegion + i * 2 + AFfunction::randomInt(0, 1);
        m_cardPocket.push_back(new Card(cardType, this));
    }

    // make random first turn card
    m_firstList.clear();
    auto neutralCard = Card::randNeutralCard();
    for (unsigned i = 0 ; i < 5 - m_playerList.length(); i++)
        m_firstList.insert(AFlib::Function::randomInt(0, m_firstList.size()),
                           Card::getNeutralCard(neutralCard[i]));
    for (auto it : m_playerList)
        m_firstList.insert(AFlib::Function::randomInt(0, m_firstList.size()),
                           Card::Type::FirstInitiative + it->clan()->type());

    // TODO choose mission to all players
    // TODO set control token to capital
    // TODO set n control token but each person (only first step)
    // TODO step by step put control token to map

    //#Turn
    // choose first player
    m_turnQueue.clear();
    bool isFound = false;
    Clan::Type firstClan = getCurrentFirstPlayer();
    for (auto it : m_playerList){
        if (it->clan()->type() == firstClan)
            isFound = true;

        if (isFound)
            m_turnQueue.push_back(it);
    }

    for (auto it : m_playerList){
        if (it->clan()->type() == firstClan)
            break;

        m_turnQueue.push_back(it);
    }

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

BattleForRokugan::Clan::Type BattleForRokugan::Game::getCurrentFirstPlayer()
{
    Clan::Type clan = Clan::Type::None;
    Card::Type card;
    for (auto it : m_firstList){
        switch (it) {
        case Card::Type::InitiativeCrab:
        case Card::Type::InitiativeCrane:
        case Card::Type::InitiativeDragon:
        case Card::Type::InitiativeLion:
        case Card::Type::InitiativePhoenix:
        case Card::Type::InitiativeScorpion:
        case Card::Type::InitiativeUnicorn:
            clan = static_cast <Clan::Type>(it - Card::Type::FirstInitiative); break;
        case Card::Type::LordOfTheLands: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement<unsigned, 7> (getClanProvinceOwned()).first;
            clan = static_cast <Clan::Type>(clanIndex);
            break;
        }
        case Card::Type::SupremeStrategist: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement<unsigned, 7> (getClanControlToken()).first;
            clan = static_cast <Clan::Type>(clanIndex);
            break;
        }
        case Card::Type::YoungEmperor: {
            if (m_phase == Phase::Pregame)
                continue;
            auto clanIndex = AFfunction::findMaxElement<unsigned, 7> (getRegionCardOwner()).first;
            clan = static_cast <Clan::Type>(clanIndex);
            break;
        }
        default: return Clan::Type::None;
        }

        card = it;
    }

    // remove taked first from list
    m_firstList.removeOne(card);
    return clan;
}

std::array<unsigned, 7> BattleForRokugan::Game::getClanControlToken() const
{
    std::array <unsigned, 7> ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <unsigned>(it->clan()->type())] = it->controlTokenCount();
    return ret;
}

std::array<unsigned, 7> BattleForRokugan::Game::getClanProvinceOwned() const
{
    std::array <unsigned, 7> ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <unsigned>(it->clan()->type())] = it->provinceCount();
    return ret;
}

std::array<unsigned, 7> BattleForRokugan::Game::getRegionCardOwner() const
{
    std::array <unsigned, 7> ret = { 0, 0, 0, 0, 0, 0, 0 };
    for (auto it : m_playerList)
        ret[static_cast <unsigned>(it->clan()->type())] = it->regionCardCount();
    return ret;
}
