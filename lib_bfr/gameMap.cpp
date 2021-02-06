#include "lib_bfr/gameMap.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/game.h"
#include "AFbase/AfFunction"

BattleForRokugan::GameMap::GameMap(QObject* parent) : QObject(parent)
{
    // init regions
    for (unsigned char i = 0; i < 11; i++)
        m_regionList.push_back(new Region(static_cast <Region::Type> (i), this));

    addLandBorder();
    addNavyBorder();
}

BattleForRokugan::Region* BattleForRokugan::GameMap::operator [](const Region::Type type) const
{
    for (auto it : m_regionList)
        if (it->type() == type)
            return it;
    return nullptr;
}

bool BattleForRokugan::GameMap::addBorder(BattleForRokugan::Region::Type type, uchar number)
{
    auto prov = findProvince(type, number);
    if (not prov)
        return false;
    auto border = new Border(prov.value(), this);
    m_listBorders.push_back(border);
    prov->get()->addBorder(border);
    return true;
}

bool BattleForRokugan::GameMap::addBorder(BattleForRokugan::Region::Type type1, unsigned char s1,
                                          BattleForRokugan::Region::Type type2, unsigned char s2)
{
    auto prov1 = findProvince(type1, s1);
    auto prov2 = findProvince(type2, s2);
    if (not prov1 or  not prov2)
        return false;
    auto border = new Border(prov1.value(), prov2.value(), this);
    m_listBorders.push_back(border);
    prov1->get()->addBorder(border);
    prov2->get()->addBorder(border);
    return true;
}

std::optional<std::shared_ptr<BattleForRokugan::Province>>
BattleForRokugan::GameMap::findProvince(BattleForRokugan::Region::Type type, unsigned char stars) const
{
    auto region = findRegion(type);
    if (region)
        return region.value()->findProvince(stars);
    return std::nullopt;
}

std::optional <BattleForRokugan::Region*>
BattleForRokugan::GameMap::findRegion(BattleForRokugan::Region::Type type) const
{
    for (auto it : m_regionList)
        if (type == it->type())
            return it;
    return std::nullopt;
}

std::list<BattleForRokugan::Clan::Type> BattleForRokugan::GameMap::minCountProvincesClan() const
{
    auto clan_list = static_cast <Game*> (parent())->getClanProvinceOwned();
    std::list <Clan::Type> ret;
    for (auto it : AFfunction::findMinIndexList <unsigned, 7> (clan_list))
        ret.push_back(static_cast <Clan::Type> (it));
    return ret;
}

std::list<BattleForRokugan::Clan::Type> BattleForRokugan::GameMap::maxCountProvincesClan(bool withToken) const
{
    std::array <unsigned, 7> clan_owner_count;
    auto game = static_cast <Game*>(parent());
    clan_owner_count = withToken ? game->getClanControlToken() : game->getClanProvinceOwned();

    std::list <Clan::Type> ret;
    for (auto it : AFfunction::findMinIndexList <unsigned, 7> (clan_owner_count))
        ret.push_back(static_cast <Clan::Type> (it));
    return ret;
}

void BattleForRokugan::GameMap::addLandBorder()
{
    // init land borders
    typedef Region::Type RegionType;
    addBorder(RegionType::Dragon, 0, RegionType::Dragon, 1);
    addBorder(RegionType::Dragon, 0, RegionType::Unicorn, 0);
    addBorder(RegionType::Dragon, 0, RegionType::Lion, 2);
    addBorder(RegionType::Dragon, 1, RegionType::Phoenix, 0);
    addBorder(RegionType::Dragon, 1, RegionType::Lion, 0);
    addBorder(RegionType::Dragon, 1, RegionType::Dragon, 2);
    addBorder(RegionType::Dragon, 2, RegionType::Phoenix, 0);
    addBorder(RegionType::Dragon, 2, RegionType::Lion, 0);
    addBorder(RegionType::Dragon, 2, RegionType::Lion, 1);
    addBorder(RegionType::Dragon, 2, RegionType::Lion, 2);
    addBorder(RegionType::Phoenix, 0, RegionType::Phoenix, 1);
    addBorder(RegionType::Phoenix, 0, RegionType::Lion, 2);
    addBorder(RegionType::Phoenix, 1, RegionType::Phoenix, 2);
    addBorder(RegionType::Phoenix, 1, RegionType::Lion, 2);
    addBorder(RegionType::Phoenix, 2, RegionType::Lion, 2);
    addBorder(RegionType::Unicorn, 0, RegionType::Unicorn, 1);
    addBorder(RegionType::Unicorn, 0, RegionType::Unicorn, 2);
    addBorder(RegionType::Unicorn, 0, RegionType::Lion, 0);
    addBorder(RegionType::Unicorn, 1, RegionType::Unicorn, 2);
    addBorder(RegionType::Unicorn, 1, RegionType::Scorpion, 0);
    addBorder(RegionType::Unicorn, 1, RegionType::Scorpion, 2);
    addBorder(RegionType::Unicorn, 2, RegionType::Crab, 0);
    addBorder(RegionType::Unicorn, 2, RegionType::Scorpion, 2);
    addBorder(RegionType::Lion, 0, RegionType::Crab, 0);
    addBorder(RegionType::Lion, 0, RegionType::Lion, 1);
    addBorder(RegionType::Lion, 1, RegionType::Scorpion, 0);
    addBorder(RegionType::Lion, 1, RegionType::Scorpion, 1);
    addBorder(RegionType::Lion, 1, RegionType::Lion, 2);
    addBorder(RegionType::Lion, 1, RegionType::Crane, 0);
    addBorder(RegionType::Lion, 1, RegionType::Crane, 1);
    addBorder(RegionType::Lion, 2, RegionType::Crane, 0);
    addBorder(RegionType::Scorpion, 0, RegionType::Scorpion, 1);
    addBorder(RegionType::Scorpion, 0, RegionType::Scorpion, 2);
    addBorder(RegionType::Scorpion, 1, RegionType::Crane, 1);
    addBorder(RegionType::Scorpion, 1, RegionType::Crane, 2);
    addBorder(RegionType::Scorpion, 1, RegionType::Crab, 1);
    addBorder(RegionType::Scorpion, 2, RegionType::Crab, 0);
    addBorder(RegionType::Scorpion, 2, RegionType::Crab, 1);
    addBorder(RegionType::Crab, 0, RegionType::Crab, 1);
    addBorder(RegionType::Crab, 0, RegionType::Crab, 2);
    addBorder(RegionType::Crab, 0, RegionType::ShadowUp);
    addBorder(RegionType::Crab, 1, RegionType::Crane, 2);
    addBorder(RegionType::Crab, 1, RegionType::Dune, 0);
    addBorder(RegionType::Crab, 1, RegionType::Crab, 2);
    addBorder(RegionType::Crab, 2, RegionType::Crab, 3);
    addBorder(RegionType::Crab, 2, RegionType::Dune, 0);
    addBorder(RegionType::Crab, 2, RegionType::ShadowUp);
    addBorder(RegionType::Crab, 3, RegionType::Dune, 2);
    addBorder(RegionType::Crab, 3, RegionType::ShadowDown);
    addBorder(RegionType::Crab, 3, RegionType::ShadowUp);
    addBorder(RegionType::Crane, 0, RegionType::Crane, 1);
    addBorder(RegionType::Crane, 1, RegionType::Crane, 2);
    addBorder(RegionType::Crane, 2, RegionType::Dune, 0);
    addBorder(RegionType::Crane, 2, RegionType::Dune, 1);
    addBorder(RegionType::Dune, 0, RegionType::Dune, 1);
    addBorder(RegionType::Dune, 0, RegionType::Dune, 2);
    addBorder(RegionType::Dune, 1, RegionType::Dune, 2);
    addBorder(RegionType::ShadowDown, 0, RegionType::ShadowUp);
}

void BattleForRokugan::GameMap::addNavyBorder()
{
    // init navy borders
    typedef Region::Type RegionType;
    addBorder(RegionType::Phoenix, 2);
    addBorder(RegionType::Lion , 2);
    addBorder(RegionType::Crane, 0);
    addBorder(RegionType::Crane, 1);
    addBorder(RegionType::Crane, 2);
    addBorder(RegionType::Dune, 1);
    addBorder(RegionType::Dune, 2);
    addBorder(RegionType::Archipelago, 0);
    addBorder(RegionType::Archipelago, 1);
    addBorder(RegionType::Archipelago, 2);
    addBorder(RegionType::Crab, 3);
    addBorder(RegionType::ShadowDown, 0);
}
