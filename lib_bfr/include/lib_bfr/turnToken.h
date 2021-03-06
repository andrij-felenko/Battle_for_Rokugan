#ifndef LIB_BFR_TURN_TOKEN_H
#define LIB_BFR_TURN_TOKEN_H

#include "bfrLib_pre.h"

class BattleForRokugan::TurnToken : public QObject
{
    Q_OBJECT
public:
    TurnToken(Player* owner, TurnTokenType type, uchar value);
    TurnToken(Player* owner, TurnTokenType type);
    Q_ENUM(TurnTokenType)
    Q_ENUM(TurnTokenStatus)

    TurnTokenType type() const;
    void setType(TurnTokenType type);

    ErrorMsg name(TurnTokenType type) const;
    ErrorMsg name() const;

    uchar value() const;
    void setValue(uchar value);
    bool setBlessing(TurnToken* token);

    Player* owner() const;

    TurnTokenStatus status() const;
    void setStatus(const TurnTokenStatus &status);

    TurnToken *blessing() const;

private:
    uchar m_value;
    Player* m_owner;
    TurnTokenType m_type;
    TurnTokenStatus m_status;
    TurnToken* m_blessing;
};

#endif // LIB_BFR_TURN_TOKEN_H
