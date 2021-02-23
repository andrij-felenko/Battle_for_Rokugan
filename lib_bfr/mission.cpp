#include <set>
#include <AFbase/AfFunction>
#include "lib_bfr/clanStats.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/map.h"
#include "lib_bfr/mission.h"
#include "lib_bfr/player.h"
#include "lib_bfr/province.h"
#include "lib_bfr/region.h"

BFR::Mission::Mission(MissionType type, Map* map, ClanStats* stats, QObject* parent)
    : QObject(parent), m_type(type), m_picked(false), m_map(map), m_stats(stats)
{
    //
}

BFR::MissionType BFR::Mission::type() const
{
    return m_type;
}

bool BFR::Mission::picked() const
{
    return m_picked;
}

void BFR::Mission::setPicked(Clan* clan)
{
    if (picked())
        return;
    m_clan = clan;
    m_picked = true;
}

int BFR::Mission::result() const { return result(m_type, m_clan, m_map, m_stats); }
int BFR::Mission::result(MissionType mission, Clan* clan, Map* map, ClanStats* stats)
{
    auto capOr2Prov = [clan, map](RegionType regType)->bool
    {
        auto region = map->operator[](regType);
        if (region->provinceOwnerCount(clan->type()) >= 2)
            return true;
        if (auto capital = region->capital(); capital)
            if (capital->owner()->clan() == clan)
                return true;
        return false;
    };

    switch (mission) {
    case MissionType::Battlefield:          return capOr2Prov(RegionType::Lion)     ? 7 : 0;
    case MissionType::EmpireRiceBowl:       return capOr2Prov(RegionType::Crane)    ? 6 : 0;
    case MissionType::GreatLibrary:         return capOr2Prov(RegionType::Phoenix)  ? 7 : 0;
    case MissionType::GreatWallOfTheNorth:  return capOr2Prov(RegionType::Dragon)   ? 6 : 0;
    case MissionType::SuburbOfTheFiveWinds: return capOr2Prov(RegionType::Unicorn)  ? 6 : 0;
    case MissionType::TheLastLineOfDefense: return capOr2Prov(RegionType::Crab)     ? 5 : 0;
    case MissionType::VaultOfSecrets:       return capOr2Prov(RegionType::Scorpion) ? 7 : 0;
    case MissionType::EmeraldEmpire: {
        typedef std::function <bool (ProvinceList)> NextProvFunc;
        NextProvFunc nextProv = [&nextProv, clan](ProvinceList list)->bool
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

            // check is it contains in 3 different region
            std::set <ClanType> clanSet;
            for (const auto &province : list)
                if (auto player = province->owner(); player)
                clanSet.insert(player->clan()->type());
            return clanSet.size() >= 3;
        };

        for (auto reg : map->m_regionList)
            for (const auto &province : reg->m_provinceList)
                if (province->owner()->clan() == clan)
                    if (nextProv({ province }))
                        return 10;

        return 0;
    }
    case MissionType::ForgottenLands:
        return map->operator[](RegionType::ShadowDown)->daimyo() == clan->type() &&
               map->operator[](RegionType::ShadowUp)->daimyo() == clan->type() ? 3 : 0;
    case MissionType::MasterOfTheSeas: {
        int navyProvinces =0;
        for (auto reg : map->m_regionList)
            for (const auto &prov : reg->m_provinceList){
                if (auto player = prov->owner(); player)
                    if (player->clan() == clan && prov->navy())
                        navyProvinces++;
                if (navyProvinces >= 6)
                    return 10;
            }
        return 0;
    }
    case MissionType::Modesty_PolitenessOfKings:
        return stats->minProvinceClan(clan->type()) ? 10 : 0;
    case MissionType::UbiquitousInfluence: {
        int i = 0;
        for (auto reg : map->m_regionList)
            if (reg->provinceOwnerCount(clan->type()) > 0)
                i++;
        return  i >= 7 ? 10 : 0;
    }
    default:;
    }
    return 0;
}

QString BFR::Mission::name() { return name(m_type); }
QString BFR::Mission::name(MissionType type)
{
    switch (type) {
    case MissionType::Battlefield:  return tr("Battlefield");
    case MissionType::GreatLibrary: return tr("Great library");
    case MissionType::EmeraldEmpire:   return tr("Emerald empire");
    case MissionType::EmpireRiceBowl:  return tr("Empire rice bowl");
    case MissionType::ForgottenLands:  return tr("Forgotten lands");
    case MissionType::VaultOfSecrets:  return tr("Vault of secrets");
    case MissionType::MasterOfTheSeas: return tr("Master of the seas");
    case MissionType::GreatWallOfTheNorth:  return tr("Great wall of the north");
    case MissionType::UbiquitousInfluence:  return tr("Ubiquitous influence");
    case MissionType::SuburbOfTheFiveWinds: return tr("Suburb of the five winds");
    case MissionType::TheLastLineOfDefense: return tr("The last line of defense");
    case MissionType::Modesty_PolitenessOfKings: return tr("Modesty - politeness of kings");
    }
    return "";
}

QString BFR::Mission::description() { return description(m_type); }
QString BFR::Mission::description(MissionType type)
{
    switch (type) {
    case MissionType::Battlefield:
        return tr("If you control a Lion Clan Capital Province or 2 provinces "
                  "in a Lion Clan Region at the end of the game, gain 7 Honor Points.");

    case MissionType::EmeraldEmpire:
        return tr("If at the end of the game you control a chain of 6 contiguous provinces "
                  "that belong to 3 different regions, you will receive 10 honor points.");

    case MissionType::EmpireRiceBowl:
        return tr("If at the end you control a Capital Province of the Crane Clan "
                  "or 2 provinces in the Crane Region, gain 6 Honor Points.");

    case MissionType::ForgottenLands:
        return tr("If you control the Shadowlands (both provinces) "
                  "at the end of the game, gain 3 honor points.");

    case MissionType::GreatLibrary:
        return tr("If at the end you control a Phoenix capital province or 2 provinces "
                  "in a Phoenix clan region, gain 7 honor points.");

    case MissionType::GreatWallOfTheNorth:
        return tr("If at the end of the game you control a Dragon clan capital province "
                  "or 2 provinces in a Dragon clan region, gain 6 honor points.");

    case MissionType::MasterOfTheSeas:
        return tr("If you control 6 coastal provinces at the end of the game, "
                  "gain 10 honor points.");

    case MissionType::Modesty_PolitenessOfKings:
        return tr("If you control the least number of provinces at the end of the game, "
                  "you will receive 10 honor points. If there is a tie, "
                  "you still complete this goal and earn honor points.");

    case MissionType::UbiquitousInfluence:
        return tr("If you control at least one province in 7 different regions "
                  "at the end of the game, you will receive 10 Honor points.");

    case MissionType::SuburbOfTheFiveWinds:
        return tr("If at the end of the game you control a Unicorn capital province "
                  "or 2 provinces in a Unicorn clan region, gain 6 honor points.");

    case MissionType::TheLastLineOfDefense:
        return tr("If at the end of the game you control a Crab capital province "
                  "or 2 provinces in the Crab clan regions, gain 5 honor points.");

    case MissionType::VaultOfSecrets:
        return tr("If at the end of the game you control a Scorpion capital province "
                  "or 2 provinces in a Scorpio clan region, gain 7 honor points.");
    }
    return "";
}

namespace BattleForRokugan {
    MissionType operator+(MissionType type, uint i)
    {
        return static_cast <MissionType>(static_cast <uint>(type) + i);
    }

    MissionType operator++(MissionType type)
    {
        return type + 1;
    }
}
