#ifndef LIB_BFR_KARTA_TOKEN_BASEMENT_H
#define LIB_BFR_KARTA_TOKEN_BASEMENT_H

#include "bfrLib_pre.h"

class battle_for_rokugan::karta::TokenBasement : public QObject
{
public:
    TokenBasement(QObject* parent = nullptr);
    token::CombatList m_combatList;

    // battle handler
    bool combatTokenContains(CombatTokenType type) const;
    virtual void pushCombatToken(token::Combat* token);

protected:
    void clearEmptyTokens();
    void removeCombatToken(token::Combat* token);
    void removeCombatToken(token::CombatList list);

    friend class handler::Battle;
};

#endif
