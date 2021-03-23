#include "lib_bfr/karta/tokenBasement.h"
#include "lib_bfr/token/combat.h"

bfr::karta::TokenBasement::TokenBasement(QObject *parent)
    :QObject(parent)
{
    //
}

bool bfr::karta::TokenBasement::combatTokenContains(CombatTokenType type) const
{
    for (auto it : m_combatList)
        if (it->type() == type)
            return true;
    return false;
}

void bfr::karta::TokenBasement::pushCombatToken(token::Combat *token)
{
    m_combatList.push_back(token);
}

void bfr::karta::TokenBasement::clearEmptyTokens()
{
    auto removeFunc = [](token::Combat* t)
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

void bfr::karta::TokenBasement::removeCombatToken(token::Combat *token)
{
    removeCombatToken(token::CombatList { token });
}

void bfr::karta::TokenBasement::removeCombatToken(token::CombatList list)
{
    auto removeFunc = [list](token::Combat* t){
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
