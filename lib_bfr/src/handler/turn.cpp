#include <AFbase/AfFunction>
#include "lib_bfr/handler/stats.h"
#include "lib_bfr/handler/turn.h"
#include "lib_bfr/object/card.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"


BFR::Handler::Turn::Turn(Stats *stats, QObject *parent)
    : QObject(parent), m_stats(stats)
{
    m_firstCard = new Object::Card(CardType::FirstPlayer, this);
    connect(this, &Turn::turnChanged, this, &Turn::updateTurnQueue);
}

void BFR::Handler::Turn::nextTurn()
{
    m_turn++;
    m_subTurnLeft = 5 * m_playerList.count();
    emit turnChanged(m_turn);
}

void BFR::Handler::Turn::reset(Object::PlayerList list)
{
    // create all pregame component
    m_turn = 0;
    m_position = 0;
    m_phase = Phase::Pregame;
    m_playerList = list;

    // make random first turn card
    m_firstList.clear();
    auto neutralCard = Object::Card::randNeutralCard();
    for (unsigned i = 0 ; i < 5 - m_playerList.length(); i++)
        m_firstList.insert(AFlib::Function::randomInt(0, m_firstList.size()),
                           Object::Card::getNeutralCard(neutralCard[i]));

    m_subTurnLeft = (1 << (5 - m_playerList.count())) + 3;
    for (auto it : m_playerList){
        m_firstList.insert(AFfunction::randomInt(0, m_firstList.size()),
                           CardType::FirstInitiative + it->clan()->type());
        it->setStartCtrlToken(m_subTurnLeft);
    }
    m_subTurnLeft *= m_playerList.count();

    updateTurnQueue();
    for (auto it : m_playerList){
        using namespace Object;
        connect(it, &Player::startCtrlTokenPlaced, this, &Turn::nextPosition);
        connect(it, &Player::combatTokenPlaced,    this, &Turn::nextPosition);
    }
}

void BFR::Handler::Turn::clear()
{
    m_firstList.clear();
}

BFR::ClanType BFR::Handler::Turn::getCurrentFirstPlayer()
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
        case CardType::MasterOfGovernance: {
            if (m_phase == Phase::Pregame)
                continue;
            clan = m_stats->maxProvinceClan().first();
            break;
        }
        case CardType::MasterOfTactics: {
            if (m_phase == Phase::Pregame)
                continue;
            clan = m_stats->maxCtrlToken(true).first();
            break;
        }
        case CardType::RiseOfAnEmpire: {
            if (m_phase == Phase::Pregame)
                continue;
            clan = m_stats->maxTerritoryCard().first();
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

// must call only 1 time in each game turn (up to 5 time maximum)
void BFR::Handler::Turn::updateTurnQueue()
{
    for (auto it : m_playerList){
        if (it->position() == 0)
            it->removeFirstCard();
        it->setPosition(-1);
    }
    m_firstCard->m_used = false;

    bool isFound = false;
    int currentPosition = 0;
    ClanType firstClan = getCurrentFirstPlayer();
    for (auto it : m_playerList){
        if (it->clan()->type() == firstClan){
            isFound = true;
            it->addFirstCard(m_firstCard);
        }

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

void BFR::Handler::Turn::nextPosition()
{
    if (m_position + 1 == m_playerList.count()){
        m_position = 0;
        if (m_subTurnLeft == 0){
            if (m_turn == 5){
                m_phase = Phase::Postgame;
                emit gameFinished();
            }
            else {
                emit turnPlacedFinished();
                if (m_turn == 0){
                    m_turn++;
                    m_phase = Phase::Game;
                    m_subTurnLeft = 5 * m_playerList.count();
                    emit turnChanged(m_turn);
                }
            }
        }
        else
            m_subTurnLeft--;
    }
    else {
        m_position++;
        emit positionChanged(m_position);
    }
}
