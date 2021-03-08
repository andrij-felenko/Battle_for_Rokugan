#include "token/honor.h"

BattleForRokugan::Token::Honor::Honor(uint value, QObject *parent)
    : QObject(parent), m_value(value)
{
    //
}

uint BattleForRokugan::Token::Honor::honor() const
{
    return m_value;
}
