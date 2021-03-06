#include "lib_bfr/object/card.h"
#include "lib_bfr/object/clan.h"
#include "lib_bfr/object/player.h"
#include "lib_baseAF/afFunction.h"
#include "lib_bfr/karta/province.h"
#include "lib_bfr/token/combat.h"
#include "lib_bfr/token/province.h"

bfr::object::Card::Card(CardType type, Player *owner)
    : QObject(owner), m_owner(owner), m_type(type), m_used(false)
{
    //
}

bfr::CardType bfr::object::Card::type()   const { return m_type; }
bool          bfr::object::Card::isUsed() const { return m_used; }
void          bfr::object::Card::  use ()       { m_used = true; }

bfr::CardType bfr::object::Card::getNeutralCard(uint i)
{
    return CardType::MasterOfGovernance + i;
}

bool bfr::object::Card::isInitiative(CardType type)
{
    return type >= CardType::FirstInitiative && type <= CardType::LastInitiative;
}

bool bfr::object::Card::isTerritory(CardType type)
{
    return type >= CardType::FirstTerritory && type <= CardType::LastTerritory;
}

bfr::object::Player *bfr::object::Card::getOwner() const
{
    return m_owner;
}

void bfr::object::Card::setOwner(Player *owner)
{
    m_owner = owner;
}

bfr::CombatTokenType bfr::object::Card::useFirstPlayer(token::Combat *token)
{
    if (m_type != CardType::FirstPlayer)
        return CombatTokenType::None;

    token->setStatus(StatusTokenType::Reserve);
    setOwner(nullptr);
    return token->type();
}

bfr::CombatTokenType bfr::object::Card::useScout(bfr::token::Combat *token)
{
    if (m_type != CardType::Scout)
        return CombatTokenType::None;

    use();
    return token->type();
}

void bfr::object::Card::useShugenja(bfr::token::Combat *token)
{
    if (m_type != CardType::Shugenja)
        return;

    token->show();
    // TODO add pause
    token->setStatus(StatusTokenType::Discharge);
    use();
}

void bfr::object::Card::useTerritoryCrab_FeatsOfEngineering(bfr::karta::Province *province,
                                                            bfr::karta::Province *pushProvince)
{
    if (m_type != CardType::TerritoryCrab_FeatsOfEngineering)
        return;

    if (province->owner() == m_owner){
        if (pushProvince->owner() == m_owner)
            pushProvince->addControlOnToken(3);
        else
            ;// TODO set error
    }
    province->setProvinceToken(ProvinceTokenType::ScorchedEarth);
    use();
}

void bfr::object::Card::useTerritoryCrab_Promotion(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryCrab_Promotion)
        return;

    province->setProvinceToken(ProvinceTokenType::Harbor);
    use();
}

void bfr::object::Card::useTerritoryCrane_CodeOfHonor(bfr::karta::Province *prov1,
                                                      bfr::karta::Province *prov2)
{
    if (m_type != CardType::TerritoryCrane_CodeOfHonor)
        return;

    prov1->pushHonor(1);
    prov2->pushHonor(1);
    use();
}

void bfr::object::Card::useTerritoryCrane_DiplomaticMission(bfr::karta::Province *provPeace, karta::Province *provToken)
{
    if (m_type != CardType::TerritoryCrane_DiplomaticMission)
        return;

    provPeace->setProvinceToken(ProvinceTokenType::Peace);
    if (provToken && provPeace->owner() != m_owner)
        provToken->addControlOnToken(2);
    use();
}

void bfr::object::Card::useTerritoryDragon_SacredGround(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryDragon_SacredGround)
        return;

    province->setProvinceToken(ProvinceTokenType::Shrine);
    use();
}

void bfr::object::Card::useTerritoryDragon_StrengthOfPurpose(bfr::karta::Province *prov1, bfr::karta::Province *prov2)
{
    if (m_type != CardType::TerritoryDragon_StrengthOfPurpose)
        return;

    prov1->addControlOnToken(1);
    prov2->addControlOnToken(1);
    use();
}

void bfr::object::Card::useTerritoryIslands_PirateRaids(bfr::karta::Province *provScorch, bfr::karta::Province *provToken)
{
    if (m_type != CardType::TerritoryIslands_PirateRaids)
        return;

    if (provToken && provScorch->owner() == m_owner)
        provToken->addControlOnToken(3);

    provScorch->setProvinceToken(ProvinceTokenType::ScorchedEarth);
    use();
}

void bfr::object::Card::useTerritoryIslands_PortOfProsperity(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryIslands_PortOfProsperity)
        return;

    province->pushHonor(2);
    use();
}

void bfr::object::Card::useTerritoryLion_Bushido(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryLion_Bushido)
        return;

    province->setProvinceToken(ProvinceTokenType::HonorBonusFull);
    use();
}

void bfr::object::Card::useTerritoryLion_HonorableFight(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryLion_HonorableFight)
        return;

    province->setProvinceToken(ProvinceTokenType::Glory);
    use();
}

void bfr::object::Card::useTerritoryMountains_AshigaruLevies(bfr::karta::Province *prov1, bfr::karta::Province *prov2, bfr::karta::Province *prov3)
{
    if (m_type != CardType::TerritoryMountains_AshigaruLevies)
        return;

    if (not prov1->isShadowProvince())
        prov1->setProvinceToken(ProvinceTokenType::ProtectionBonus);

    if (not prov2->isShadowProvince())
        prov2->setProvinceToken(ProvinceTokenType::ProtectionBonus);

    if (not prov3->isShadowProvince())
        prov3->setProvinceToken(ProvinceTokenType::ProtectionBonus);

    use();
}

void bfr::object::Card::useTerritoryMountains_BountifulHarvest(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryMountains_BountifulHarvest)
        return;

    province->addControlOnToken(2);
    use();
}

void bfr::object::Card::useTerritoryPhoenix_AidOfTheKami(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryPhoenix_AidOfTheKami)
        return;

    province->setProvinceToken(ProvinceTokenType::ProtectionBonus2);
    use();
}

void bfr::object::Card::useTerritoryPhoenix_BlessTheLands(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryPhoenix_AidOfTheKami)
        return;

    if (not province->scorched())
        return;

    province->removeProvinceToken(ProvinceTokenType::ScorchedEarth);
    m_owner->takeProvince(province);
    province->addControlOnToken(2);
    use();
}

void bfr::object::Card::useTerritoryScorpion_FomentRebellion(bfr::karta::Province *province)
{
    if (m_type != CardType::TerritoryScorpion_FomentRebellion)
        return;

    if (not province->provinceTokenContains(ProvinceTokenType::Peace))
        return;

    if (province->owner() == m_owner)
        province->addControlOnToken(2);
    use();
}

void bfr::object::Card::useTerritoryShadowlandsSouth_InspireFear(bfr::karta::Province *province,
                                                                 bfr::token::Province *token1,
                                                                 bfr::token::Province *token2)
{
    if (m_type != CardType::TerritoryShadowlandsSouth_InspireFear)
        return;

    province->popControlToken();
    token1->province()->removeProvinceToken(token1->type());
    if (token2)
        token2->province()->removeProvinceToken(token2->type());
    use();
}

void bfr::object::Card::useTerritoryUnicorn_Reinforcement(bfr::token::Combat *dis1,
                                                          bfr::token::Combat *dis2,
                                                          bfr::token::Combat *ast1,
                                                          bfr::token::Combat *ast2)
{
    if (m_type != CardType::TerritoryUnicorn_Reinforcement)
        return;

    dis1->setStatus(StatusTokenType::Assets);
    dis2->setStatus(StatusTokenType::Assets);
    ast1->setStatus(StatusTokenType::Reserve);
    ast2->setStatus(StatusTokenType::Reserve);
    use();
}

void bfr::object::Card::useTerritoryUnicorn_CulturalExchange(bfr::karta::Province *prov1, bfr::karta::Province *prov2)
{
    if (m_type != CardType::TerritoryUnicorn_CulturalExchange)
        return;

    prov1->swapAllContent(prov2);
    use();
}

QString bfr::object::Card::name() const
{
    switch (m_type) {
    case CardType::FirstPlayer:        return tr("First Player");
    case CardType::Scout:              return tr("Scout");
    case CardType::Shugenja:           return tr("Shugenja");
    case CardType::MasterOfGovernance: return tr("Master of Governance");
    case CardType::MasterOfTactics:    return tr("Master of Tactics");
    case CardType::RiseOfAnEmpire:     return tr("Rise of an Empire");

    case CardType::TerritoryCrab_FeatsOfEngineering:  return tr("Feats of engineering");
    case CardType::TerritoryCrab_Promotion:           return tr("Promotion");
    case CardType::TerritoryCrane_CodeOfHonor:        return tr("Code of Honor");
    case CardType::TerritoryCrane_DiplomaticMission:  return tr("Diplomatic Mission");
    case CardType::TerritoryDragon_SacredGround:      return tr("Sacred ground");
    case CardType::TerritoryDragon_StrengthOfPurpose: return tr("Strength of purpose");
    case CardType::TerritoryIslands_PirateRaids:      return tr("Pirate raids");
    case CardType::TerritoryIslands_PortOfProsperity: return tr("Port of prosperity");
    case CardType::TerritoryLion_Bushido:             return tr("Bushido");
    case CardType::TerritoryLion_HonorableFight:      return tr("Honorable fight");
    case CardType::TerritoryMountains_AshigaruLevies:   return tr("Ashigaru levies");
    case CardType::TerritoryMountains_BountifulHarvest: return tr("Bountiful Harvest");
    case CardType::TerritoryPhoenix_AidOfTheKami:       return tr("Aid of the Kami");
    case CardType::TerritoryPhoenix_BlessTheLands:      return tr("Bless the lands");
    case CardType::TerritoryScorpion_FomentRebellion:   return tr("Foment rebellion");
    case CardType::TerritoryScorpion_SpyNetwork:        return tr("Spy Network");
    case CardType::TerritoryShadowlandsNorth_DarkFavors:     return tr("Dark favors");
    case CardType::TerritoryShadowlandsNorth_PurgeTheWeak:   return tr("Purge the weak");
    case CardType::TerritoryShadowlandsSouth_AnimateTheDead: return tr("Animate the dead");
    case CardType::TerritoryShadowlandsSouth_InspireFear:    return tr("Inspire fear");
    case CardType::TerritoryUnicorn_CulturalExchange: return tr("Cultural Exchange");
    case CardType::TerritoryUnicorn_Reinforcement:    return tr("Reinforcement");
    default:;
    }
    return Clan::name(static_cast <ClanType> (m_type - CardType::InitiativeCrab));
}

QString bfr::object::Card::description() const
{
    switch (m_type) {
    case CardType::FirstPlayer:
        return tr("Choose one combat token on the board belonging to any player. "
                  "Look at the token without revealing it to the other players, "
                  "then return the token to its owner???s token pool.");

    case CardType::MasterOfGovernance:
        return tr("The player who controls the highest number of provinces"
                  " is the first player.");

    case CardType::Scout:
        return tr("Take 1 battle token of any opponent from the board. Look at the front of it,"
                  " without showing the others, and return the token to its place.");

    case CardType::Shugenja:
        return tr("Draw 1 Battle Token from any opponent from the board. "
                  "Open its front side to everyone and send it to the owner's reset.");

    case CardType::MasterOfTactics:
        return tr("The player who has the highest number of control tokens (faceup and facedown)"
                  " on the board is the first player.");

    case CardType::RiseOfAnEmpire:
        return tr("The player who has the highest number of territory cards is the first player.");

    case CardType::TerritoryIslands_PirateRaids:
        return tr("Place one scorched earth token in any province. "
                  "If you place the scorched earth token in a province you control, "
                  "place three of your control tokens faceup in another province you control.");
    case CardType::TerritoryIslands_PortOfProsperity:
        return tr("Choose a non-Shadowlands province and place one +2 honor token in it.");

    case CardType::TerritoryCrab_FeatsOfEngineering:
        return tr("Choose one army, navy, or shinobi token in your discard pile "
                  "and return it to your hand. Then choose one combat token in your hand "
                  "and either discard it or return it to your token pool.");
    case CardType::TerritoryCrab_Promotion:
        return tr("Choose a landlocked province and place the harbor token in it."
                  " That province is now a coastal province.");

    case CardType::TerritoryCrane_CodeOfHonor:
        return tr("Choose two different non-Shadowlands provinces "
                  "and place one +1 honor token in each province.");
    case CardType::TerritoryCrane_DiplomaticMission:
        return tr("Place one peace token in any province. "
                  "If you place the peace token in an opponent???s province, "
                  "add two of your control tokens faceup to a province you control.");

    case CardType::TerritoryDragon_SacredGround:
        return tr("Choose a province and place the shrine token in it. "
                  "That province cannot be attacked, but attacks can originate from it.");
    case CardType::TerritoryDragon_StrengthOfPurpose:
        return tr("Choose two different provinces you control and "
                  "add one of your control tokens faceup to each of those provinces.");

    case CardType::TerritoryMountains_AshigaruLevies:
        return tr("Choose three different non-Shadowlands provinces "
                  "and place one +1 defense token in each province.");
    case CardType::TerritoryMountains_BountifulHarvest:
        return tr("Choose one province you control "
                  "and place two of your control tokens faceup in that province.");

    case CardType::TerritoryShadowlandsSouth_InspireFear:
        return tr("Remove one of your control tokens from a non-Shadowlands province."
                  " Then remove up to two special tokens from the board.");
    case CardType::TerritoryShadowlandsSouth_AnimateTheDead:
        return tr("Remove one of your control tokens from a non-Shadowlands province. "
                  "Then choose one combat token in your discard pile and place it "
                  "faceup on the board, following all normal placement rules. "
                  "(Then place a combat token from your hand as usual).");

    case CardType::TerritoryShadowlandsNorth_DarkFavors:
        return tr("Remove one of your control tokens from a non-Shadowlands province."
                  " Then look at up to four combat tokens on the board (without revealing them)."
                  " Reveal and discard one of those tokens.");
    case CardType::TerritoryShadowlandsNorth_PurgeTheWeak:
        return tr("Discard one combat token from your hand "
                  "(you will not place a combat token this turn). "
                  "Then choose two combat tokens on the board. Reveal and discard each token.");

    case CardType::TerritoryLion_Bushido:
        return tr("Choose a non-Shadowlands province and place the 4-honor token in it, "
                  "covering its printed honor value. That province???s printed honor value is now 4.");
    case CardType::TerritoryLion_HonorableFight:
        return tr("Choose a province and place the battlefield token in it. "
                  "That province cannot be targeted by raid tokens.");

    case CardType::TerritoryPhoenix_AidOfTheKami:
        return tr("Choose a non-Shadowlands provinces and place one +2 defense token in it.");
    case CardType::TerritoryPhoenix_BlessTheLands:
        return tr("Remove one scorched earth token from any province. "
                  "Then place two of your control tokens in that province and flip them faceup.");

    case CardType::TerritoryScorpion_FomentRebellion:
        return tr("Remove one peace token from any province. "
                  "If you remove a peace token from a province you control, "
                  "add two of your control tokens faceup to that province.");
    case CardType::TerritoryScorpion_SpyNetwork:
        return tr("Choose another player and look at the tokens in that player???s hand. "
                  "That player cannot use his or her bluff token this round.");

    case CardType::TerritoryUnicorn_CulturalExchange:
        return tr("Choose a province you control and a province controlled by an opponent. "
                  "Swap all of the control tokens in your province with all of the control tokens"
                  " in the opponent???s province (preserving the faceup or facedown status of each).");
    case CardType::TerritoryUnicorn_Reinforcement:
        return tr("Choose two army tokens in your discard pile and return them to your hand. "
                  "Then return two combat tokens in your hand and either discard them "
                  "or return them to your token pool.");
    default:;
    }
    return "";
}

array_u3 bfr::object::Card::randNeutralCard()
{
    array_u3 ret = { 0, 0, 0 };
    ret[AFlib::Function::randomInt(0, 2)] = 1;
    while (true){
        uint i = AFlib::Function::randomInt(0, 2);
        if (ret[i] == 0){
            ret[i] = 2;
            break;
        }
    }
    return ret;
}

namespace battle_for_rokugan {
    CardType operator+(CardType type, uint i)
    {
        return static_cast <CardType> (static_cast <uint> (type) + i);
    }

    CardType operator-(CardType left, CardType right)
    {
        uint value = static_cast <int> (left) - static_cast <int> (right);
        return static_cast <CardType> (value);
    }

    CardType operator+(CardType card, ClanType clan)
    {
        uint value = static_cast <int> (card) + static_cast <int> (clan);
        return static_cast <CardType> (value);
    }
}
