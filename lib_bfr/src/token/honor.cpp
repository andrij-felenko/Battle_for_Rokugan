#include "token/honor.h"

bfr::token::Honor::Honor(uint value, QObject *parent)
    : QObject(parent), m_value(value)
{
    //
}

uint bfr::token::Honor::honor() const
{
    return m_value;
}
