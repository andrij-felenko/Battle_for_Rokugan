#include "AFbase/AfFunction"
#include "lib_bfr/border.h"
#include "lib_bfr/map.h"
#include "lib_bfr/province.h"
#include "lib_bfr/region.h"

BFR::Map::Map(QObject *parent) : QObject(parent)
{
    // init regions
    for (unsigned char i = 0; i < 11; i++)
        m_regionList.push_back(new Region(static_cast <RegionType>(i), this));

    addLandBorder();
    addNavyBorder();
}

BFR::Region* BFR::Map::operator [](const RegionType type) const
{
    for (auto it : m_regionList)
        if (it->type() == type)
            return it;
    return nullptr;
}

void BFR::Map::clear()
{
    // TODO clear all
}

void BattleForRokugan::Map::openTokens()
{
    setShowTurnToken(true);
}

void BattleForRokugan::Map::newTurn()
{
    setShowTurnToken(false);
}

bool BattleForRokugan::Map::showTurnToken() const
{
    return m_showTurnToken;
}

bool BFR::Map::addBorder(RegionType type, uchar_v v)
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

bool BFR::Map::addBorder(RegionType type1, unsigned char s1,
                         RegionType type2, unsigned char s2)
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

bool BFR::Map::addBorder(RegionType type1, uchar_v s1,
                         RegionType type2, uchar_v s2)
{
    bool ret = true;
    for (auto v1 : s1)
        for (auto v2 : s2)
            if (not addBorder(type1, v1, type2, v2)){
                ret = false;
                // TODO add warning about filed add border
            }
    return ret;
}

bool BattleForRokugan::Map::addBorder(RegionType type, uchar_pair_v v)
{
    return addBorder(type, type, v);
}

bool BattleForRokugan::Map::addBorder(RegionType type1, RegionType type2, uchar_pair_v v)
{
    bool ret = true;
    for (auto it : v)
        if (not addBorder(type1, it.first, type2, it.second))
            ret = false;
    return ret;
}

BFR::Province* BFR::Map::findProvince(RegionType type, unsigned char stars) const
{
    auto region = findRegion(type);
    if (region)
        return region->findProvince(stars);
    return nullptr;
}

BFR::Region* BFR::Map::findRegion(RegionType type) const
{
    for (auto it : m_regionList)
        if (type == it->type())
            return it;
    return nullptr;
}

void BFR::Map::addLandBorder()
{
    // init land borders
    addBorder(RegionType::Crane,    {{0, 1}, {1, 2}});
    addBorder(RegionType::Dragon,   {{0, 1}, {1, 2}});
    addBorder(RegionType::Lion,     {{0, 1}, {1, 2}});
    addBorder(RegionType::Phoenix,  {{0, 1}, {1, 2}});
    addBorder(RegionType::Scorpion, {{0, 1}, {0, 2}});
    addBorder(RegionType::Dune,     {{0, 1}, {0, 2}, {1, 2}});
    addBorder(RegionType::Unicorn,  {{0, 1}, {0, 2}, {1, 2}});
    addBorder(RegionType::Crab,     {{0, 1}, {0, 2}, {1, 2}, {2, 3}});

    addBorder(RegionType::Dragon,   RegionType::Lion,     {{0, 2}, {1, 0}});
    addBorder(RegionType::Unicorn,  RegionType::Scorpion, {{1, 0}, {1, 2}, {2, 2}});
    addBorder(RegionType::Lion,     RegionType::Crane,    {{1, 0}, {1 ,1}, {2, 0}});
    addBorder(RegionType::Scorpion, RegionType::Crab,     {{1, 1}, {2, 0}, {2, 1}});
    addBorder(RegionType::Crab,     RegionType::Dune,     {{1, 0}, {2, 0}, {3, 2}});
    addBorder(RegionType::Crab,     RegionType::ShadowUp, {{3, 0}, {2, 0}, {0, 0}});

    addBorder(RegionType::Crab,       1, RegionType::Crane,   2);
    addBorder(RegionType::Dragon,     0, RegionType::Unicorn);
    addBorder(RegionType::Unicorn,    2, RegionType::Crab);
    addBorder(RegionType::Unicorn,    0, RegionType::Lion);
    addBorder(RegionType::Lion,       0, RegionType::Crab);
    addBorder(RegionType::Crab,       3, RegionType::ShadowDown);
    addBorder(RegionType::ShadowDown, 0, RegionType::ShadowUp);

    addBorder(RegionType::Lion,     { 1 },       RegionType::Scorpion, { 0, 1 });
    addBorder(RegionType::Scorpion, { 1 },       RegionType::Crane,    { 1, 2 });
    addBorder(RegionType::Crane,    { 2 },       RegionType::Dune,     { 0, 1 });
    addBorder(RegionType::Dragon,   { 2   },     RegionType::Lion,     { 0, 1, 2 });
    addBorder(RegionType::Dragon,   { 1, 2 },    RegionType::Phoenix,  { 0 });
    addBorder(RegionType::Phoenix,  { 0, 1, 2 }, RegionType::Lion,     { 2 });
}

void BFR::Map::addNavyBorder()
{
    // init navy borders
    addBorder(RegionType::Phoenix,     uchar_v { 2 });
    addBorder(RegionType::Lion ,       uchar_v { 2 });
    addBorder(RegionType::Crab,        uchar_v { 3 });
    addBorder(RegionType::ShadowDown,  uchar_v { 0 });
    addBorder(RegionType::Dune,        { 1, 2 });
    addBorder(RegionType::Crane,       { 0, 1, 2 });
    addBorder(RegionType::Archipelago, { 0, 1, 2 });
}

void BattleForRokugan::Map::setShowTurnToken(bool showTurnToken)
{
    if (m_showTurnToken == showTurnToken)
        return;

    m_showTurnToken = showTurnToken;
    emit showTurnTokenChanged(m_showTurnToken);
    if (m_showTurnToken)
        emit allTokenOpened();
}
