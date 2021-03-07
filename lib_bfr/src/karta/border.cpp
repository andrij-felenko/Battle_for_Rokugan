#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/province.h"

BFR::Karta::Border::Border(Province* prov, QObject *parent)
    : TokenBasement(parent), m_type(BorderType::Navy),
      m_province1(prov), m_province2(nullptr)
{
    //
}

BFR::Karta::Border::Border(Province* prov1, Province* prov2, QObject *parent)
    : TokenBasement(parent), m_type(BorderType::Land),
      m_province1(prov1), m_province2(prov2)
{
    //
}

BFR::Karta::Province* BFR::Karta::Border::province1() const { return m_province1; }
BFR::Karta::Province* BFR::Karta::Border::province2() const { return m_province2; }

BFR::Token::Combat* BattleForRokugan::Karta::Border::combatToken() const
{
    if (m_combatList.count() > 0)
        return m_combatList[0];

    return nullptr;
}
BFR::BorderType BFR::Karta::Border::type() const
{
    if (province1()->provinceTokenContains(ProvinceTokenType::Harbor) ||
        province2()->provinceTokenContains(ProvinceTokenType::Harbor))
        return BorderType::Navy;

    return m_type;
}

void BFR::Karta::Border::setType(BorderType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

void BFR::Karta::Border::pushCombatToken(Token::Combat *token)
{
    if (m_combatList.count() > 0)
        return;
    TokenBasement::pushCombatToken(token);
}

void BFR::Karta::Border::clear()
{
    removeCombatToken(m_combatList);
}
