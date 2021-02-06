#include "lib_bfr/border.h"

BattleForRokugan::Border::Border(std::shared_ptr<Province> prov, QObject *parent)
    : QObject(parent), m_type(Type::Navy), m_province1(prov), m_province2(nullptr)
{
    //
}

BattleForRokugan::Border::Border(std::shared_ptr<Province> prov1, std::shared_ptr<Province> prov2,
                                 QObject *parent)
    : QObject(parent), m_type(Type::Land), m_province1(prov1), m_province2(prov2)
{
    //
}

BattleForRokugan::Border::Type BattleForRokugan::Border::type() const
{
    return m_type;
}

void BattleForRokugan::Border::setType(const BattleForRokugan::Border::Type &type)
{
    if (type == m_type)
        return;
    m_type = type;
}

void BattleForRokugan::Border::clear()
{
    setToken(TurnToken::Type::None);
}

std::shared_ptr<BattleForRokugan::Province> BattleForRokugan::Border::province2() const
{
    return m_province2;
}

std::shared_ptr<BattleForRokugan::Province> BattleForRokugan::Border::province1() const
{
    return m_province1;
}

BattleForRokugan::TurnToken::Type BattleForRokugan::Border::token() const
{
    return m_token;
}

void BattleForRokugan::Border::setToken(const TurnToken::Type &token)
{
    m_token = token;
}
