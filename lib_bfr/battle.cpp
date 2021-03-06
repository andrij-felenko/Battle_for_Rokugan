#include "lib_bfr/battle.h"
#include "lib_bfr/border.h"
#include "lib_bfr/clan.h"
#include "lib_bfr/map.h"
#include "lib_bfr/player.h"
#include "lib_bfr/province.h"
#include "lib_bfr/provinceToken.h"
#include "lib_bfr/region.h"
#include "lib_bfr/turnToken.h"
#include <QtCore/QMap>

BattleForRokugan::Battle::Battle(Map *map, QObject *parent)
    : QObject(parent), m_map(map)
{
    //
}

void BattleForRokugan::Battle::reset(PlayerList playerList)
{
    m_playerList = playerList;
}

void BattleForRokugan::Battle::run()
{
    removeNotFormatPlaced();
    scorcheEarthAndDiplomacy();

    for (auto regType = RegionType::First; regType <= RegionType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            calculateBattle(province);
            province->clearTurnToken(true);
        }
    }

    emit battleFinished();
}

void BattleForRokugan::Battle::removeNotFormatPlaced()
{
    for (auto regType = RegionType::First; regType > RegionType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            province->clearEmptyTokens();

            TurnTokenList list;
            for (auto token : province->m_turnTokenList){
                if (token->type() == TTT::Empty)
                    continue;

                else if (token->type() == TTT::Navy && not province->navy())
                    list.push_back(token);

                // sabotage can be only with sinobi or nearby of player teritory
                else if (token->type() == TTT::Sabotage){
                    bool canSabotage = province->turnTokenContains(TTT::Shinobi);
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
            province->removeTurnToken(list);
        }
    }

    for (auto b : m_map->m_listBorders){
        b->clearEmptyTokens();
        TurnTokenList list;
        for (auto token : b->m_turnTokenList){
            switch (token->type()) {
            case TTT::Army: {
                if (b->type() == BorderType::Navy)
                    list.push_back(token);
                break;
            }
            case TTT::Navy: {
                if (b->type() == BorderType::Land)
                    list.push_back(token);
                break;
            }
            case TTT::Diplomacy:
            case TTT::Sabotage:
            case TTT::Shinobi: list.push_back(token); break;
            default:;
            }
        }
        b->removeTurnToken(list);
    }
}

void BattleForRokugan::Battle::scorcheEarthAndDiplomacy()
{
    // fist of all we burn the ground
    for (auto regType = RegionType::First; regType > RegionType::Last; ++regType){
        auto region = m_map->operator[](regType);
        for (uint i = 0; i < region->provinceCount(); i++){
            auto province = region->operator[](i);
            if (province->turnTokenContains(TurnTokenType::Sabotage)){
                province->setProvinceToken(ProvinceTokenType::ScorchedEarth);
                province->owner()->untakeProvince(province);
            }
            else if (province->turnTokenContains(TurnTokenType::Diplomacy))
                province->setProvinceToken(ProvinceTokenType::Peace);
            else
                continue;

            province->clearTurnToken(true);
        }
    }
}

void BattleForRokugan::Battle::calculateBattle(Province *province)
{
    auto owner = province->owner();
    auto provClan = ClanType::None;

    // calculate power of army by every clan
    QMap <ClanType, uint> power;

    // insert defends value
    if (owner){
        provClan = owner->clan()->type();
        power.insert(provClan, province->defends());

        for (auto token : province->m_turnTokenList)
            power.insert(provClan, power[provClan] + token->value());
    }
    else
        power.insert(ClanType::None, province->defends());

    // check borders to found attacking army
    for (auto b : province->m_borderList){
        auto token = b->turnToken();
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
    if (power[provClan] > maxValue || winnerClan == ClanType::None){
        // TODO smth
    }
    // 2. attacker win
    else if (maxValue > power[provClan]){
        // TODO smth
    }
}
