#include "lib_bfr/karta/tokenBasement.h"
#include "lib_bfr/token/combat.h"

BFR::Karta::TokenBasement::TokenBasement(QObject *parent)
    :QObject(parent)
{
    //
}

bool BFR::Karta::TokenBasement::combatTokenContains(CombatTokenType type) const
{
    for (auto it : m_combatList)
        if (it->type() == type)
            return true;
    return false;
}

void BFR::Karta::TokenBasement::pushCombatToken(Token::Combat *token)
{
    m_combatList.push_back(token);
}

void BFR::Karta::TokenBasement::clearEmptyTokens()
{
    auto removeFunc = [](Token::Combat* t)
    {
        if (t->type() == CombatTokenType::Empty){
            if (t->blessing())
                t->blessing()->setStatus(STT::Discharge);
            t->setStatus(STT::Assets);
            return true;
        }
        return false;
    };
    m_combatList.erase(std::remove_if(m_combatList.begin(), m_combatList.end(),
                                         removeFunc), m_combatList.end());
}

void BFR::Karta::TokenBasement::removeCombatToken(Token::Combat *token)
{
    removeCombatToken(Token::CombatList { token });
}

void BFR::Karta::TokenBasement::removeCombatToken(Token::CombatList list)
{
    auto removeFunc = [list](Token::Combat* t){
        for (auto it : list)
            if (it == t){
                it->setStatus(STT::Discharge);
                if (it->blessing())
                    it->blessing()->setStatus(STT::Discharge);
                return true;
            }
        return false;
    };
    m_combatList.erase(std::remove_if(m_combatList.begin(), m_combatList.end(),
                                         removeFunc), m_combatList.end());
}
