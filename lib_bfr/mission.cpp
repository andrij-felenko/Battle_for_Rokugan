#include "lib_bfr/mission.h"
#include "lib_bfr/border.h"
#include "lib_bfr/game.h"
#include <functional>
#include <set>

using namespace BattleForRokugan;

Mission::Mission(const Type &type, QObject *parent)
    : QObject(parent), m_type(type)
{
    //
}

QString Mission::description(const Mission::Type &type)
{
    switch (type) {
    case Type::Battlefield:
        return tr("If you control a Lion Clan Capital Province or 2 provinces "
                  "in a Lion Clan Region at the end of the game, gain 7 Honor Points.");

    case Type::EmeraldEmpire:
        return tr("If at the end of the game you control a chain of 6 contiguous provinces "
                  "that belong to 3 different regions, you will receive 10 honor points.");

    case Type::EmpireRiceBowl:
        return tr("If at the end you control a Capital Province of the Crane Clan "
                  "or 2 provinces in the Crane Region, gain 6 Honor Points.");

    case Type::ForgottenLands:
        return tr("If you control the Shadowlands (both provinces) "
                  "at the end of the game, gain 3 honor points.");

    case Type::GreatLibrary:
        return tr("If at the end you control a Phoenix capital province or 2 provinces "
                  "in a Phoenix clan region, gain 7 honor points.");

    case Type::GreatWallOfTheNorth:
        return tr("If at the end of the game you control a Dragon clan capital province "
                  "or 2 provinces in a Dragon clan region, gain 6 honor points.");

    case Type::MasterOfTheSeas:
        return tr("If you control 6 coastal provinces at the end of the game, "
                  "gain 10 honor points.");

    case Type::Modesty_PolitenessOfKings:
        return tr("If you control the least number of provinces at the end of the game, "
                  "you will receive 10 honor points. If there is a tie, "
                  "you still complete this goal and earn honor points.");

    case Type::UbiquitousInfluence:
        return tr("If you control at least one province in 7 different regions "
                  "at the end of the game, you will receive 10 Honor points.");

    case Type::SuburbOfTheFiveWinds:
        return tr("If at the end of the game you control a Unicorn capital province "
                  "or 2 provinces in a Unicorn clan region, gain 6 honor points.");

    case Type::TheLastLineOfDefense:
        return tr("If at the end of the game you control a Crab capital province "
                  "or 2 provinces in the Crab clan regions, gain 5 honor points.");

    case Type::VaultOfSecrets:
        return tr("If at the end of the game you control a Scorpion capital province "
                  "or 2 provinces in a Scorpio clan region, gain 7 honor points.");
    }
    return "";
}

QString Mission::description()
{
    return description(m_type);
}

QString Mission::name(const Mission::Type &type)
{
    switch (type) {
    case Type::Battlefield:  return tr("Battlefield");
    case Type::GreatLibrary: return tr("Great library");
    case Type::EmeraldEmpire:   return tr("Emerald empire");
    case Type::EmpireRiceBowl:  return tr("Empire rice bowl");
    case Type::ForgottenLands:  return tr("Forgotten lands");
    case Type::VaultOfSecrets:  return tr("Vault of secrets");
    case Type::MasterOfTheSeas: return tr("Master of the seas");
    case Type::GreatWallOfTheNorth:  return tr("Great wall of the north");
    case Type::UbiquitousInfluence:  return tr("Ubiquitous influence");
    case Type::SuburbOfTheFiveWinds: return tr("Suburb of the five winds");
    case Type::TheLastLineOfDefense: return tr("The last line of defense");
    case Type::Modesty_PolitenessOfKings: return tr("Modesty - politeness of kings");
    }
    return "";
}

QString Mission::name()
{
    return name(m_type);
}

int Mission::result(Mission::Type mission, Clan::Type clan, const GameMap* const map)
{
    switch (mission) {
    case Type::Battlefield: {
        auto lion = map->operator[](Region::Type::Lion);
        if (lion->provinceOwnerCount(clan) >= 2)
            return 7;
        if (auto capital = lion->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 7;
        return 0;
    }
    case Type::EmeraldEmpire: {
        typedef std::list <std::shared_ptr <Province>> ProvinceList;
        std::function <bool (ProvinceList)> nextProv = [&nextProv, clan](ProvinceList list)->bool
        {
            for (const auto &it : list.back()->neighboringProvinces()){
                // if we found not clan border than check result
                if (it.get()->clanOwner() != clan)
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
            std::set <Clan::Type> clanSet;
            for (const auto &province : list)
                clanSet.insert(province->clanOwner());
            return clanSet.size() >= 3;
        };

        for (auto reg : map->m_regionList)
            for (const auto &prov : reg->m_provinceList)
                if (prov.get()->clanOwner() == clan)
                    if (nextProv({ prov }))
                        return 10;

        return 0;
    }
    case Type::EmpireRiceBowl: {
        auto crane = map->operator[](Region::Type::Crane);
        if (crane->provinceOwnerCount(clan) >= 2)
            return 6;
        if (auto capital = crane->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 6;
        return 0;
    }
    case Type::ForgottenLands:
        return map->operator[](Region::Type::ShadowDown)->daimyoRegion() == clan &&
               map->operator[](Region::Type::ShadowUp)->daimyoRegion() == clan ? 3 : 0;
    case Type::GreatLibrary: {
        auto phoenix = map->operator[](Region::Type::Phoenix);
        if (phoenix->provinceOwnerCount(clan) >= 2)
            return 7;
        if (auto capital = phoenix->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 7;
        return 0;
    }
    case Type::GreatWallOfTheNorth: {
        auto dragon = map->operator[](Region::Type::Dragon);
        if (dragon->provinceOwnerCount(clan) >= 2)
            return 6;
        if (auto capital = dragon->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 6;
        return 0;
    }
    case Type::MasterOfTheSeas: {
        int navyProvinces =0;
        for (auto reg : map->m_regionList)
            for (const auto &prov : reg->m_provinceList){
                if (prov.get()->clanOwner() == clan && prov.get()->navy())
                    navyProvinces++;
                if (navyProvinces >= 6)
                    return 10;
            }
        return 0;
    }
    case Type::Modesty_PolitenessOfKings: {
        auto min = map->minCountProvincesClan();
        return std::find(min.begin(), min.end(), clan) == min.end() ? 0 : 10;
    }
    case Type::UbiquitousInfluence: {
        int i = 0;
        for (auto reg : map->m_regionList)
            if (reg->provinceOwnerCount(clan) > 0)
                i++;
        return  i >= 7 ? 10 : 0;
    }
    case Type::SuburbOfTheFiveWinds: {
        auto unicorn = map->operator[](Region::Type::Unicorn);
        if (unicorn->provinceOwnerCount(clan) >= 2)
            return 6;
        if (auto capital = unicorn->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 6;
        return 0;
    }
    case Type::TheLastLineOfDefense: {
        auto crab = map->operator[](Region::Type::Crab);
        if (crab->provinceOwnerCount(clan) >= 2)
            return 5;
        if (auto capital = crab->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 5;
        return 0;
    }
    case Type::VaultOfSecrets: {
        auto scorpion = map->operator[](Region::Type::Scorpion);
        if (scorpion->provinceOwnerCount(clan) >= 2)
            return 7;
        if (auto capital = scorpion->capital(); capital)
            if (capital->get()->clanOwner() == clan)
                return 7;
        return 0;
    }
    default:;
    }
    return 0;
}

int Mission::result(Clan::Type clan, const GameMap * const map) const
{
    return result(m_type, clan, map);
}
