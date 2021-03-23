#include <set>
#include <AFbase/AfFunction>
#include "lib_bfr/handler/stats.h"
#include "lib_bfr/karta/map.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/karta/territory.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/object/secretObjective.h"

bfr::object::SecretObjective::SecretObjective(SOT type, karta::Map* map,
                                              handler::Stats* stats, QObject* parent)
    : QObject(parent), m_type(type), m_picked(false), m_map(map), m_stats(stats)
{
    //
}

bfr::SOT bfr::object::SecretObjective::type() const
{
    return m_type;
}

bool bfr::object::SecretObjective::picked() const
{
    return m_picked;
}

void bfr::object::SecretObjective::setPicked(Clan* clan)
{
    if (picked())
        return;
    m_clan = clan;
    m_picked = true;
}

int bfr::object::SecretObjective::result() const { return result(m_type, m_clan, m_map, m_stats); }
int bfr::object::SecretObjective::result(SOT secretObjective, Clan* clan,
                                         karta::Map* map, handler::Stats* stats)
{
    // capital or 2 province
    auto capOr2Prov = [clan, map](TerritoryType terType)->bool
    {
        auto territory = map->operator[](terType);
        if (territory->provinceOwnerCount(clan->type()) >= 2)
            return true;
        if (auto capital = territory->capital(); capital)
            if (capital->owner()->clan() == clan)
                return true;
        return false;
    };

    switch (secretObjective) {
    case SOT::PlainsOfBattle:       return capOr2Prov(TerritoryType::Lion)     ? 7 : 0;
    case SOT::RiceBowlOfTheEmpire:  return capOr2Prov(TerritoryType::Crane)    ? 6 : 0;
    case SOT::GreatLibrary:         return capOr2Prov(TerritoryType::Phoenix)  ? 7 : 0;
    case SOT::GreatWallOfTheNorth:  return capOr2Prov(TerritoryType::Dragon)   ? 6 : 0;
    case SOT::CourtOfTheFiveWinds:  return capOr2Prov(TerritoryType::Unicorn)  ? 6 : 0;
    case SOT::TheLastLineOfDefense: return capOr2Prov(TerritoryType::Crab)     ? 5 : 0;
    case SOT::DenOfSecrets:         return capOr2Prov(TerritoryType::Scorpion) ? 7 : 0;
    case SOT::EmeraldEmpire: {
        typedef std::function <bool (karta::ProvinceList)> NextProvFunc;
        NextProvFunc nextProv = [&nextProv, clan](karta::ProvinceList list)->bool
        {
            for (const auto &it : list.back()->neighboringProvinces()){
                // if we found not clan border than check result
                if (it->owner()->clan() != clan)
                    break;

                // if we found province where we already added, than check result
                if (std::find(list.begin(), list.end(), it) != list.end())
                    break;

                list.push_back(it);
                if (nextProv(list))
                    return true;
            }
            if (list.size() < 6)
                return false;

            // check is it contains in 3 different territory
            std::set <ClanType> clanSet;
            for (const auto &province : list)
                if (auto player = province->owner(); player)
                clanSet.insert(player->clan()->type());
            return clanSet.size() >= 3;
        };

        for (auto reg : map->m_territoryList)
            for (const auto &province : reg->m_provinceList)
                if (province->owner()->clan() == clan)
                    if (nextProv({ province }))
                        return 10;

        return 0;
    }
    case SOT::ReclaimingLostLands:
        return map->operator[](TerritoryType::ShadowlandsSouth)->daimyo() == clan->type() &&
               map->operator[](TerritoryType::ShadowlandsNorth)->daimyo() == clan->type() ? 3 : 0;
    case SOT::WayOfTheSail: {
        int navyProvinces =0;
        for (auto reg : map->m_territoryList)
            for (const auto &prov : reg->m_provinceList){
                if (auto player = prov->owner(); player)
                    if (player->clan() == clan && prov->navy())
                        navyProvinces++;
                if (navyProvinces >= 6)
                    return 10;
            }
        return 0;
    }
    case SOT::WayOfHumility:
        return stats->minProvinceClan(clan->type()) ? 10 : 0;
    case SOT::WebOfInfluence: {
        int i = 0;
        for (auto reg : map->m_territoryList)
            if (reg->provinceOwnerCount(clan->type()) > 0)
                i++;
        return  i >= 7 ? 10 : 0;
    }
    default:;
    }
    return 0;
}

QString bfr::object::SecretObjective::name() { return name(m_type); }
QString bfr::object::SecretObjective::name(SOT type)
{
    switch (type) {
    case SOT::PlainsOfBattle:       return tr("Plains of battle");
    case SOT::GreatLibrary:         return tr("Great library");
    case SOT::EmeraldEmpire:        return tr("Emerald empire");
    case SOT::RiceBowlOfTheEmpire:  return tr("Rice bow of the empire");
    case SOT::ReclaimingLostLands:  return tr("Reclaiming lost lands");
    case SOT::DenOfSecrets:         return tr("Den of secrets");
    case SOT::WayOfTheSail:         return tr("Way of the sail");
    case SOT::GreatWallOfTheNorth:  return tr("Great wall of the north");
    case SOT::WebOfInfluence:       return tr("Web of influence");
    case SOT::CourtOfTheFiveWinds:  return tr("Court of the five winds");
    case SOT::TheLastLineOfDefense: return tr("The last line of defense");
    case SOT::WayOfHumility:        return tr("Way of humility");
    }
    return "";
}

QString bfr::object::SecretObjective::description() { return description(m_type); }
QString bfr::object::SecretObjective::description(SOT type)
{
    switch (type) {
    case SOT::PlainsOfBattle:
        return tr("At the end of the game, if you control either the Lion capital "
                  "or two provinces in the Lion territory, you earn 7 honor.");

    case SOT::EmeraldEmpire:
        return tr("At the end of the game, if you control six consecutively adjacent "
                  "provinces that span three different territories, you earn 10 honor.");

    case SOT::RiceBowlOfTheEmpire:
        return tr("At the end of the game, if you control either the Crane capital "
                  "or two provinces in the Crane territory, you earn 6 honor.");

    case SOT::ReclaimingLostLands:
        return tr("At the end of the game, if you control both Shadowlands provinces,"
                  " you earn 3 honor.");

    case SOT::GreatLibrary:
        return tr("At the end of the game, if you control either the Phoenix capital"
                  " or two provinces in the Phoenix territory, you earn 7 honor.");

    case SOT::GreatWallOfTheNorth:
        return tr("At the end of the game, if you control either the Dragon capital "
                  "or two provinces in the Dragon territory, you earn 6 honor");

    case SOT::WayOfTheSail:
        return tr("At the end of the game, if you control six coastal provinces,"
                  " you earn 10 honor.");

    case SOT::WayOfHumility:
        return tr("At the end of the game, if you control the fewest provinces,"
                  " you earn 10 honor.");

    case SOT::WebOfInfluence:
        return tr("At the end of the game, if you control at least one province "
                  "in each of seven different territories, you earn 10 honor.");

    case SOT::CourtOfTheFiveWinds:
        return tr("At the end of the game, if you control either the Unicorn capital"
                  " or two provinces in the Unicorn territory, you earn 6 honor.");

    case SOT::TheLastLineOfDefense:
        return tr("At the end of the game, if you control either the Crab capital "
                  "or two provinces in the Crab territory, you earn 5 honor.");

    case SOT::DenOfSecrets:
        return tr("At the end of the game, if you control either the Scorpion capital"
                  " or two provinces in the Scorpion territory, you earn 7 honor.");
    }
    return "";
}

namespace battle_for_rokugan {
    SOT operator+(SOT type, uint i)
    {
        return static_cast <SOT>(static_cast <uint>(type) + i);
    }

    SOT operator++(SOT type)
    {
        return type + 1;
    }
}
