#ifndef LIB_BFR_BORDER_H
#define LIB_BFR_BORDER_H

#include "bfrLib_pre.h"
#include "../turnTokenPlace.h"

class BattleForRokugan::Border : public BFR::TurnTokenPlace
{
    Q_OBJECT
public:
    Border(Province* prov, QObject* parent);
    Border(Province* prov1, Province* prov2, QObject* parent);
    Q_ENUM(BorderType)

    BorderType type() const;
    void setType(BorderType type);

    TurnToken* turnToken() const;
    virtual void pushTurnToken(TurnToken* turnToken) override final;
    void clear();

    Province* province1() const;
    Province* province2() const;

private:
    BorderType m_type;
    Province* m_province1;
    Province* m_province2;

    friend class Battle;
    friend class Province;
};

#endif // LIB_BFR_BORDER_H
