#ifndef LIB_BFR_KARTA_TOKEN_BASEMENT_H
#define LIB_BFR_KARTA_TOKEN_BASEMENT_H

#include "bfrLib_pre.h"

class BattleForRokugan::Karta::TokenBasement : public QObject
{
public:
    TokenBasement(QObject* parent = nullptr);
    Token::CombatList m_combatList;

    // battle handler
    bool combatTokenContains(CombatTokenType type) const;
    virtual void pushCombatToken(Token::Combat* token);

protected:
    void clearEmptyTokens();
    void removeCombatToken(Token::Combat* token);
    void removeCombatToken(Token::CombatList list);

    friend class Handler::Battle;
};

#endif
