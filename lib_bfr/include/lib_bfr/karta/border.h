#ifndef LIB_BFR_KARTA_BORDER_H
#define LIB_BFR_KARTA_BORDER_H

#include "bfrLib_pre.h"
#include "tokenBasement.h"

class battle_for_rokugan::karta::Border : public TokenBasement
{
    Q_OBJECT
public:
    Border(Province* prov, QObject* parent);
    Border(Province* prov1, Province* prov2, QObject* parent);
    Q_ENUM(BorderType)

    BorderType type() const;
    void setType(BorderType type);

    token::Combat* combatToken() const;
    virtual void pushCombatToken(token::Combat* token) override final;
    void clear();

    Province* province1() const;
    Province* province2() const;

private:
    BorderType m_type;
    Province* m_province1;
    Province* m_province2;

    friend class handler::Battle;
    friend class karta::Province;
};

#endif
