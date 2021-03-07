#include "token/control.h"

BattleForRokugan::Token::Control::Control(bool isOn, ClanType clan, QObject *parent)
    : QObject(parent), m_isOn(isOn), m_clan(clan)
{
    //
}

bool BattleForRokugan::Token::Control::isOn() const
{
    return m_isOn;
}

uint BattleForRokugan::Token::Control::defends() const
{
    return m_isOn ? m_clan == ClanType::Crab ? 2 : 1 : 0;
}

uint BattleForRokugan::Token::Control::stars() const
{
    return m_isOn ? 1 : 0;
}
