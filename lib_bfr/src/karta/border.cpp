#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/province.h"

bfr::karta::Border::Border(Province* prov, QObject *parent)
    : TokenBasement(parent), m_type(BorderType::Navy),
      m_province1(prov), m_province2(nullptr)
{
    //
}

bfr::karta::Border::Border(Province* prov1, Province* prov2, QObject *parent)
    : TokenBasement(parent), m_type(BorderType::Land),
      m_province1(prov1), m_province2(prov2)
{
    //
}

bfr::karta::Province* bfr::karta::Border::province1() const { return m_province1; }
bfr::karta::Province* bfr::karta::Border::province2() const { return m_province2; }

bfr::token::Combat* bfr::karta::Border::combatToken() const
{
    if (m_combatList.count() > 0)
        return m_combatList[0];

    return nullptr;
}
bfr::BorderType bfr::karta::Border::type() const
{
    if (province1()->provinceTokenContains(ProvinceTokenType::Harbor) ||
        province2()->provinceTokenContains(ProvinceTokenType::Harbor))
        return BorderType::Navy;

    return m_type;
}

void bfr::karta::Border::setType(BorderType type)
{
    if (type == m_type)
        return;
    m_type = type;
}

void bfr::karta::Border::pushCombatToken(token::Combat *token)
{
    if (m_combatList.count() > 0)
        return;
    TokenBasement::pushCombatToken(token);
}

void bfr::karta::Border::clear()
{
    removeCombatToken(m_combatList);
}
