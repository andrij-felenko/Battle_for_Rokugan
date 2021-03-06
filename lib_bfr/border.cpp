#include "lib_bfr/border.h"
#include "lib_bfr/province.h"

BFR::Border::Border(Province* prov, QObject *parent)
    : TurnTokenPlace(parent), m_type(BorderType::Navy),
      m_province1(prov), m_province2(nullptr)
{
    //
}

BFR::Border::Border(Province* prov1, Province* prov2, QObject *parent)
    : TurnTokenPlace(parent), m_type(BorderType::Land),
      m_province1(prov1), m_province2(prov2)
{
    //
}

BFR::Province* BFR::Border::province1() const { return m_province1; }
BFR::Province* BFR::Border::province2() const { return m_province2; }

BFR::TurnToken *BattleForRokugan::Border::turnToken() const
{
    if (m_turnTokenList.count() > 0)
        return m_turnTokenList[0];

    return nullptr;
}
BFR::BorderType      BFR::Border::type()      const
{
    if (province1()->provinceTokenContains(ProvinceTokenType::Harbor) ||
        province2()->provinceTokenContains(ProvinceTokenType::Harbor))
        return BorderType::Navy;

    return m_type;
}

void BFR::Border::setType(BorderType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

void BattleForRokugan::Border::pushTurnToken(TurnToken *turnToken)
{
    if (m_turnTokenList.count() > 0)
        return;
    TurnTokenPlace::pushTurnToken(turnToken);
}

void BFR::Border::clear()
{
    removeTurnToken(m_turnTokenList);
}
