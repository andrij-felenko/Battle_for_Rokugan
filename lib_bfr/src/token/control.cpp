#include "token/control.h"

bfr::token::Control::Control(bool isOn, ClanType clan, QObject *parent)
    : QObject(parent), m_isOn(isOn), m_clan(clan)
{
    //
}

bool bfr::token::Control::isOn() const
{
    return m_isOn;
}

uint bfr::token::Control::defends() const
{
    return m_isOn ? m_clan == ClanType::Crab ? 2 : 1 : 0;
}

uint bfr::token::Control::stars() const
{
    return m_isOn ? 1 : 0;
}
