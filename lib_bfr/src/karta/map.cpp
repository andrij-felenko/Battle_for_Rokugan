#include "AFbase/AfFunction"
#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/map.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/karta/territory.h"

BFR::Karta::Map::Map(QObject *parent) : QObject(parent)
{
    // init regions
    for (unsigned char i = 0; i < 11; i++)
        m_territoryList.push_back(new Territory(static_cast <TerritoryType>(i), this));

    addLandBorder();
    addNavyBorder();
}

BFR::Karta::Territory* BFR::Karta::Map::operator [](const TerritoryType type) const
{
    for (auto it : m_territoryList)
        if (it->type() == type)
            return it;
    return nullptr;
}

void BFR::Karta::Map::clear()
{
    // TODO clear all
}

void BFR::Karta::Map::openTokens()
{
    setShowCombatToken(true);
}

void BFR::Karta::Map::newTurn()
{
    setShowCombatToken(false);
}

bool BFR::Karta::Map::showCombatToken() const
{
    return m_showCombatToken;
}

bool BFR::Karta::Map::addBorder(TerritoryType type, uchar_v v)
{
    bool ret = true;
    for (auto it : v){
        auto prov = findProvince(type, it);
        if (not prov){
            ret = false;
            continue;
        }
        auto border = new Border(prov, this);
        m_listBorders.push_back(border);
        prov->addBorder(border);
    }
    return ret;
}

bool BFR::Karta::Map::addBorder(TerritoryType type1, unsigned char s1,
                         TerritoryType type2, unsigned char s2)
{
    auto prov1 = findProvince(type1, s1);
    auto prov2 = findProvince(type2, s2);
    if (not prov1 or  not prov2)
        return false;
    auto border = new Border(prov1, prov2, this);
    m_listBorders.push_back(border);
    prov1->addBorder(border);
    prov2->addBorder(border);
    return true;
}

bool BFR::Karta::Map::addBorder(TerritoryType type1, uchar_v s1,
                         TerritoryType type2, uchar_v s2)
{
    bool ret = true;
    for (auto v1 : s1)
        for (auto v2 : s2)
            if (not addBorder(type1, v1, type2, v2))
                ret = false;
    return ret;
}

bool BFR::Karta::Map::addBorder(TerritoryType type, uchar_pair_v v)
{
    return addBorder(type, type, v);
}

bool BFR::Karta::Map::addBorder(TerritoryType type1, TerritoryType type2, uchar_pair_v v)
{
    bool ret = true;
    for (auto it : v)
        if (not addBorder(type1, it.first, type2, it.second))
            ret = false;
    return ret;
}

BFR::Karta::Province* BFR::Karta::Map::findProvince(TerritoryType type, unsigned char stars) const
{
    auto region = findRegion(type);
    if (region)
        return region->findProvince(stars);
    return nullptr;
}

BFR::Karta::Territory* BFR::Karta::Map::findRegion(TerritoryType type) const
{
    for (auto it : m_territoryList)
        if (type == it->type())
            return it;
    return nullptr;
}

void BFR::Karta::Map::addLandBorder()
{
    // init land borders
    addBorder(TerritoryType::Crane,    {{0, 1}, {1, 2}});
    addBorder(TerritoryType::Dragon,   {{0, 1}, {1, 2}});
    addBorder(TerritoryType::Lion,     {{0, 1}, {1, 2}});
    addBorder(TerritoryType::Phoenix,  {{0, 1}, {1, 2}});
    addBorder(TerritoryType::Scorpion, {{0, 1}, {0, 2}});
    addBorder(TerritoryType::Mountains,{{0, 1}, {0, 2}, {1, 2}});
    addBorder(TerritoryType::Unicorn,  {{0, 1}, {0, 2}, {1, 2}});
    addBorder(TerritoryType::Crab,     {{0, 1}, {0, 2}, {1, 2}, {2, 3}});

    addBorder(TerritoryType::Dragon,   TerritoryType::Lion,             {{0, 2}, {1, 0}});
    addBorder(TerritoryType::Unicorn,  TerritoryType::Scorpion,         {{1, 0}, {1, 2}, {2, 2}});
    addBorder(TerritoryType::Lion,     TerritoryType::Crane,            {{1, 0}, {1 ,1}, {2, 0}});
    addBorder(TerritoryType::Scorpion, TerritoryType::Crab,             {{1, 1}, {2, 0}, {2, 1}});
    addBorder(TerritoryType::Crab,     TerritoryType::Mountains,        {{1, 0}, {2, 0}, {3, 2}});
    addBorder(TerritoryType::Crab,     TerritoryType::ShadowlandsNorth, {{3, 0}, {2, 0}, {0, 0}});

    addBorder(TerritoryType::Crab,             1, TerritoryType::Crane,   2);
    addBorder(TerritoryType::Dragon,           0, TerritoryType::Unicorn);
    addBorder(TerritoryType::Unicorn,          2, TerritoryType::Crab);
    addBorder(TerritoryType::Unicorn,          0, TerritoryType::Lion);
    addBorder(TerritoryType::Lion,             0, TerritoryType::Crab);
    addBorder(TerritoryType::Crab,             3, TerritoryType::ShadowlandsSouth);
    addBorder(TerritoryType::ShadowlandsSouth, 0, TerritoryType::ShadowlandsNorth);

    addBorder(TerritoryType::Lion,     { 1 },       TerritoryType::Scorpion, { 0, 1 });
    addBorder(TerritoryType::Scorpion, { 1 },       TerritoryType::Crane,    { 1, 2 });
    addBorder(TerritoryType::Crane,    { 2 },       TerritoryType::Mountains,{ 0, 1 });
    addBorder(TerritoryType::Dragon,   { 2   },     TerritoryType::Lion,     { 0, 1, 2 });
    addBorder(TerritoryType::Dragon,   { 1, 2 },    TerritoryType::Phoenix,  { 0 });
    addBorder(TerritoryType::Phoenix,  { 0, 1, 2 }, TerritoryType::Lion,     { 2 });
}

void BFR::Karta::Map::addNavyBorder()
{
    // init navy borders
    addBorder(TerritoryType::Phoenix,          uchar_v { 2 });
    addBorder(TerritoryType::Lion ,            uchar_v { 2 });
    addBorder(TerritoryType::Crab,             uchar_v { 3 });
    addBorder(TerritoryType::ShadowlandsSouth, uchar_v { 0 });
    addBorder(TerritoryType::Mountains, { 1, 2 });
    addBorder(TerritoryType::Crane,     { 0, 1, 2 });
    addBorder(TerritoryType::Islands,   { 0, 1, 2 });
}

void BFR::Karta::Map::setShowCombatToken(bool showCombatToken)
{
    if (m_showCombatToken == showCombatToken)
        return;

    m_showCombatToken = showCombatToken;
    emit showCombatTokenChanged(m_showCombatToken);
    if (m_showCombatToken)
        emit allTokenOpened();
}
