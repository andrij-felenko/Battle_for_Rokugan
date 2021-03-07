#ifndef LIB_BFR_TOKEN_COMBAT_H
#define LIB_BFR_TOKEN_COMBAT_H

#include "bfrLib_pre.h"

class BattleForRokugan::Token::Combat : public QObject
{
    Q_OBJECT
public:
    Combat(Object::Player* owner, CombatTokenType type, uchar value);
    Combat(Object::Player* owner, CombatTokenType type);
    Q_ENUM(CombatTokenType)
    Q_ENUM(StatusTokenType)

    CombatTokenType type() const;
    void setType(CombatTokenType type);

    ErrorMsg name(CombatTokenType type) const;
    ErrorMsg name() const;

    uchar value() const;
    void setValue(uchar value);
    bool setBlessing(Combat* token);

    Object::Player* owner() const;

    StatusTokenType status() const;
    void setStatus(const StatusTokenType &status);

    Combat *blessing() const;

private:
    uchar m_value;
    Object::Player* m_owner;
    CombatTokenType m_type;
    StatusTokenType m_status;
    Combat* m_blessing;
};

#endif
