#include "turnTokenPlace.h"
#include "include/lib_bfr/turnToken.h"

BattleForRokugan::TurnTokenPlace::TurnTokenPlace(QObject *parent)
    :QObject(parent)
{
    //
}

bool BattleForRokugan::TurnTokenPlace::turnTokenContains(TurnTokenType type) const
{
    for (auto it : m_turnTokenList)
        if (it->type() == type)
            return true;
    return false;
}

void BattleForRokugan::TurnTokenPlace::pushTurnToken(TurnToken *turnToken)
{
    m_turnTokenList.push_back(turnToken);
}

void BattleForRokugan::TurnTokenPlace::clearEmptyTokens()
{
    auto removeFunc = [](TurnToken* t)
    {
        if (t->type() == TurnTokenType::Empty){
            if (t->blessing())
                t->blessing()->setStatus(TTS::Discharge);
            t->setStatus(TTS::Assets);
            return true;
        }
        return false;
    };
    m_turnTokenList.erase(std::remove_if(m_turnTokenList.begin(), m_turnTokenList.end(),
                                         removeFunc), m_turnTokenList.end());
}

void BattleForRokugan::TurnTokenPlace::removeTurnToken(TurnToken *turnToken)
{
    // TODO
}

void BattleForRokugan::TurnTokenPlace::removeTurnToken(TurnTokenList list)
{
    auto removeFunc = [list](TurnToken* t){
        for (auto it : list)
            if (it == t){
                it->setStatus(TTS::Discharge);
                if (it->blessing())
                    it->blessing()->setStatus(TTS::Discharge);
                return true;
            }
        return false;
    };
    m_turnTokenList.erase(std::remove_if(m_turnTokenList.begin(), m_turnTokenList.end(),
                                         removeFunc), m_turnTokenList.end());
}

BFR::TurnToken *BattleForRokugan::TurnTokenPlace::popTurnToken(TurnToken *turnToken)
{
    // TODO
}

void BattleForRokugan::TurnTokenPlace::setTurnToken(ProvinceToken *provToken)
{
    // TODO
}
