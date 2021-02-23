#ifndef LIB_BFR_TURN_TOKEN_H
#define LIB_BFR_TURN_TOKEN_H

#include "bfrLib_pre.h"

class BattleForRokugan::TurnToken : public QObject
{
    Q_OBJECT
public:
    TurnToken(TurnTokenType type, uchar value, QObject* parent);
    TurnToken(TurnTokenType type, QObject* parent);
    Q_ENUM(TurnTokenType)

    TurnTokenType type() const;
    void setType(TurnTokenType type);

    ErrorMsg name(TurnTokenType type) const;
    ErrorMsg name() const;

    uchar value() const;
    void setValue(uchar value);

private:
    TurnTokenType m_type;
    uchar m_value;
};

#endif // LIB_BFR_TURN_TOKEN_H
