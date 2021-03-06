#ifndef LIB_BFR_TURN_TOKEN_PLACE_H
#define LIB_BFR_TURN_TOKEN_PLACE_H

#include "include/bfrLib_pre.h"

class BattleForRokugan::TurnTokenPlace : public QObject
{
public:
    TurnTokenPlace(QObject* parent = nullptr);
    TurnTokenList m_turnTokenList;

    // battle handler
    bool turnTokenContains(TurnTokenType type) const;
    virtual void pushTurnToken(TurnToken* turnToken);

protected:
    void clearEmptyTokens();
    void removeTurnToken(TurnToken* turnToken);
    void removeTurnToken(TurnTokenList list);
    TurnToken *popTurnToken(TurnToken* turnToken);
    void setTurnToken(ProvinceToken* provToken);

    friend class Battle;
};

#endif // LIB_BFR_TURN_TOKEN_PLACE_H
