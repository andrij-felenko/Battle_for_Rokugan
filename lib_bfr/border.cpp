#include "lib_bfr/border.h"

BFR::Border::Border(Province* prov, QObject *parent)
    : QObject(parent), m_type(BorderType::Navy),
      m_province1(prov), m_province2(nullptr)
{
    //
}

BFR::Border::Border(Province* prov1, Province* prov2, QObject *parent)
    : QObject(parent), m_type(BorderType::Land),
      m_province1(prov1), m_province2(prov2)
{
    //
}

BFR::Province* BFR::Border::province1() const { return m_province1; }
BFR::Province* BFR::Border::province2() const { return m_province2; }
BFR::TurnTokenType   BFR::Border::token()     const { return m_token; }
BFR::BorderType      BFR::Border::type()      const { return m_type; }

void BFR::Border::setToken(TurnTokenType token)
{
    m_token = token;
}

void BFR::Border::setType(BorderType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

void BFR::Border::clear()
{
    setToken(TurnTokenType::None);
}
