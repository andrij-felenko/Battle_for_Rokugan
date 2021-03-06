#ifndef LIB_BFR_TOKEN_COMBAT_H
#define LIB_BFR_TOKEN_COMBAT_H

#include "bfrLib_pre.h"

class battle_for_rokugan::token::Combat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool show READ isShow WRITE show NOTIFY showChanged)
public:
    Combat(object::Player* owner, CombatTokenType type, uchar value);
    Combat(object::Player* owner, CombatTokenType type);
    Q_ENUM(CombatTokenType)
    Q_ENUM(StatusTokenType)

    CombatTokenType type() const;
    void setType(CombatTokenType type);

    ErrorMsg name(CombatTokenType type) const;
    ErrorMsg name() const;

    uchar value() const;
    void setValue(uchar value);
    bool setBlessing(Combat* token);

    object::Player* owner() const;

    StatusTokenType status() const;
    void setStatus(const StatusTokenType &status);

    Combat *blessing() const;

    bool isShow() const;

public slots:
    void show(bool show = true);

signals:
    void showChanged(bool show);

private:
    uchar m_value;
    object::Player* m_owner;
    CombatTokenType m_type;
    StatusTokenType m_status;
    Combat* m_blessing;
    bool m_show;
};

#endif
