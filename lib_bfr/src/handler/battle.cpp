#include "lib_bfr/handler/battle.h"
#include "lib_bfr/karta/border.h"
#include "lib_bfr/karta/map.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/karta/territory.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_bfr/token/combat.h"
#include "lib_bfr/token/province.h"
#include <QtCore/QMap>

BattleForRokugan::Handler::Battle::Battle(Karta::Map *map, QObject *parent)
    : QObject(parent), m_map(map)
{
    //
}

void BattleForRokugan::Handler::Battle::reset(Object::PlayerList playerList)
{
    m_playerList = playerList;
}

void BattleForRokugan::Handler::Battle::run()
{
    removeNotFormatPlaced();
    scorcheEarthAndDiplomacy();

    for (auto regType = TerritoryType::First; regType <= TerritoryType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            calculateBattle(province);
            province->clearCombatToken(true);
        }
    }

    emit battleFinished();
}

void BattleForRokugan::Handler::Battle::removeNotFormatPlaced()
{
    for (auto regType = TerritoryType::First; regType <= TerritoryType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            province->clearEmptyTokens();

            Token::CombatList list;
            for (auto token : province->m_combatList){
                if (token->type() == CTT::Empty)
                    continue;

                else if (token->type() == CTT::Navy && not province->navy())
                    list.push_back(token);

                // sabotage can be only with sinobi or nearby of player teritory
                else if (token->type() == CTT::Raid){
                    bool canSabotage = province->combatTokenContains(CTT::Shinobi);
                    if (not canSabotage)
                        for (auto it : province->neighboringProvinces())
                            if (it->owner() == token->owner()){
                                canSabotage = true;
                                break;
                            }
                    if (not canSabotage)
                        list.push_back(token);
                }
            }
            province->removeCombatToken(list);
        }
    }

    for (auto b : m_map->m_listBorders){
        b->clearEmptyTokens();
        Token::CombatList list;
        for (auto token : b->m_combatList){
            switch (token->type()) {
            case CTT::Army: {
                if (b->type() == BorderType::Navy)
                    list.push_back(token);
                break;
            }
            case CTT::Navy: {
                if (b->type() == BorderType::Land)
                    list.push_back(token);
                break;
            }
            case CTT::Diplomacy:
            case CTT::Raid:
            case CTT::Shinobi: list.push_back(token); break;
            default:;
            }
        }
        b->removeCombatToken(list);
    }
}

void BattleForRokugan::Handler::Battle::scorcheEarthAndDiplomacy()
{
    // fist of all we burn the ground
    for (auto regType = TerritoryType::First; regType <= TerritoryType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            if (province->combatTokenContains(CombatTokenType::Raid)){
                province->setProvinceToken(ProvinceTokenType::ScorchedEarth);
                province->owner()->untakeProvince(province);
            }
            else if (province->combatTokenContains(CombatTokenType::Diplomacy))
                province->setProvinceToken(ProvinceTokenType::Peace);
            else
                continue;

            province->clearCombatToken(true);
        }
    }
}

void BattleForRokugan::Handler::Battle::calculateBattle(Karta::Province *province)
{
    auto owner = province->owner();
    auto provClan = ClanType::None;

    // calculate power of army by every clan
    QMap <ClanType, uint> power;

    // insert defends value
    if (owner){
        provClan = owner->clan()->type();
        power.insert(provClan, province->defends());

        for (auto token : province->m_combatList)
            power.insert(provClan, power[provClan] + token->value());
    }
    else
        power.insert(ClanType::None, province->defends());

    // check borders to found attacking army
    for (auto b : province->m_borderList){
        auto token = b->combatToken();
        if (not token)
            continue;

        if (owner)
            if (token->owner() == owner)
                continue;

        power.insert(token->owner()->clan()->type(),
                     power[token->owner()->clan()->type()] + token->value());
    }

    // crane clan ability
    if (power.contains(ClanType::Crane))
        power.insert(ClanType::Crane, power[ClanType::Crane] + 1);

    // check is battle happened
    if (power.count() < 2)
        return;

    // battle
    uint maxValue = 0;
    ClanType winnerClan = ClanType::None;
    for (auto it = power.begin(); it != power.end(); ++it){
        if (it.key() == provClan)
            continue;

        if (it.value() > maxValue){
            maxValue = it.value();
            winnerClan = it.key();
        }
        else if (it.value() == maxValue)
            winnerClan = ClanType::None;
    }

    // result handler
    // 1. defender win
    if (power[provClan] > maxValue || winnerClan == ClanType::None)
        province->addControlOnToken();
    // 2. attacker win
    else if (maxValue > power[provClan]){
        for (auto it : m_playerList)
            if (it->clan()->type() == winnerClan)
                it->takeProvince(province);
    }
}
