#ifndef LIB_BFR_TOKEN_CONTROL_H
#define LIB_BFR_TOKEN_CONTROL_H

#include "bfrLib_pre.h"
#include "province.h"

class battle_for_rokugan::token::Control : public QObject
{
    Q_OBJECT
public:
    Control(bool isOn, ClanType clan, QObject* parent);

    bool isOn() const;

    uint defends() const;
    uint stars() const;

private:
    bool m_isOn;
    ClanType m_clan;
};

#endif
