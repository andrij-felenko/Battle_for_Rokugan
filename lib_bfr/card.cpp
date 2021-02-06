#include "lib_bfr/card.h"
#include "lib_baseAF/afFunction.h"
#include "lib_bfr/clan.h"

BattleForRokugan::Card::Card(const Type type, QObject *parent)
    : QObject(parent), m_type(type), m_used(false)
{
    //
}

QString BattleForRokugan::Card::name() const
{
    switch (m_type) {
    case Type::FirstPlayer:       return tr("First Player");
    case Type::LordOfTheLands:    return tr("Lord of the Lands");
    case Type::Intelligence:      return tr("Intelligence");
    case Type::Shugendja:         return tr("Shugendja");
    case Type::SupremeStrategist: return tr("Supreme Strategist");
    case Type::YoungEmperor:      return tr("Young Emperor");
    case Type::RegionArchipelago_PirateRaids: return tr("Pirate Raids");
    case Type::RegionArchipelago_Prosperity:  return tr("Prosperity");
    case Type::RegionCrab_Castling:  return tr("Castling");
    case Type::RegionCrab_SeaAccess: return tr("Sea Access");
    case Type::RegionCrane_CodeOfHonor:        return tr("Code of Honor");
    case Type::RegionCrane_DiplomaticMission:  return tr("Diplomatic Mission");
    case Type::RegionDragon_BlessedLand:       return tr("Blessed Land");
    case Type::RegionDragon_ObjectiveMovement: return tr("Objective Movement");
    case Type::RegionDune_AshigaruMilitia:  return tr("Ashigaru Militia");
    case Type::RegionDune_BountifulHarvest: return tr("Bountiful Harvest");
    case Type::RegionLandOfShadowDown_DominionOfTerror: return tr("Raise Dead");
    case Type::RegionLandOfShadowDown_RaiseDead:        return tr("Dominion of Terror");
    case Type::RegionLandOfShadowUp_DealWithEvil:   return tr("Deal with Evil");
    case Type::RegionLandOfShadowUp_KillingTheWeak: return tr("Killing the Weak");
    case Type::RegionLion_Bushido:        return tr("Bushido");
    case Type::RegionLion_GloriousBattle: return tr("Glorious Battle");
    case Type::RegionPhoenix_KamiSupport: return tr("Kami Support");
    case Type::RegionPhoenix_Purge:       return tr("Purge");
    case Type::RegionScorpion_FiresOfRebellion: return tr("Fires of Rebellion");
    case Type::RegionScorpion_SpyNetwork:       return tr("Spy Network");
    case Type::RegionUnicorn_CulturalExchange:  return tr("Cultural Exchange");
    case Type::RegionUnicorn_Reinforcement:     return tr("Reinforcement");
    default:;
    }
    return Clan::name(static_cast <Clan::Type> (static_cast <unsigned>(m_type) -
                                                static_cast <unsigned>(Type::InitiativeCrab)));
}

QString BattleForRokugan::Card::description() const
{
    switch (m_type) {
    case Type::FirstPlayer:
        return tr("(You may play this card at the start of your turn during the Placement Phase.) "
                  "Take any player's battle token from the board. Look at the front of it "
                  "without showing the rest of the players, and then mix the token "
                  "into the owner's personal supply.");

    case Type::LordOfTheLands:
        return tr("The player who controls the most provinces becomes the first player.");

    case Type::Intelligence:
        return tr("(You may play this card at the beginning of your turn during the Deployment Phase.) "
                  "Take 1 battle token of any opponent from the board. Look at the front of it, "
                  "without showing the others, and return the token to its place.");

    case Type::Shugendja:
        return tr("(You may play this card at the start of your turn during the Placement Phase.) "
                  "Draw 1 Battle Token from any opponent from the board. "
                  "Open its front side to everyone and send it to the owner's reset.");

    case Type::SupremeStrategist:
        return tr("The player with the most control tokens on the board "
                  "(both face up and down) becomes the first player.");

    case Type::YoungEmperor:
        return tr("The player with the most region cards becomes the first player.");

    case Type::RegionArchipelago_PirateRaids:
        return tr("Select a province and place a scorched earth token on it. If you control "
                  "that province, place 3 control tokens faceup and another province you control.");
    case Type::RegionArchipelago_Prosperity:
        return tr("Select a province (other than Shadowlands) and place a +2 Honor Bonus token there.");

    case Type::RegionCrab_Castling:
        return tr("Select 1 Army, Fleet, or Shinobi token from your discard "
                  "and return it to your asset. Then choose 1 battle token from your asset "
                  "and either discard it or mix it into your personal supply.");
    case Type::RegionCrab_SeaAccess:
        return tr("Select a continental province and place a harbor token in it. "
                  "This province is now considered a coastal province.");

    case Type::RegionCrane_CodeOfHonor:
        return tr("Select 2 provinces(excluding shadow lands) and place a 1 Honor Bonus token in each.");
    case Type::RegionCrane_DiplomaticMission:
        return tr("Select a province and place a peace token in it. If another player controls "
                  "the province, place 2 control tokens faceup on any province you control.");

    case Type::RegionDragon_BlessedLand:
        return tr("Select a province and place a shrine token on it. This province cannot be attacked, "
                  "but the player who controls the province can attack neighboring provinces from it.");
    case Type::RegionDragon_ObjectiveMovement:
        return tr("Choose 2 provinces you control and place 1 control token face up on each province.");

    case Type::RegionDune_AshigaruMilitia:
        return tr("Select 3 provinces (excluding Shadowlands) and place a +1 Defense Bonus token "
                  "on each province.");
    case Type::RegionDune_BountifulHarvest:
        return tr("Choose a province you control and place 2 control tokens there face up.");

    case Type::RegionLandOfShadowDown_DominionOfTerror:
        return tr("Remove your control token from any province other than the Shadowlands. "
                  "Then remove 2 or fewer Special Tokens from the board.");
    case Type::RegionLandOfShadowDown_RaiseDead:
        return tr("Remove your control token from any province other than the Shadowlands. "
                  "Then, choose a battle token from your discard and place it face up on the board, "
                  "observing the rest of the placement rules. After that, "
                  "place a battle token from your asset as usual.");

    case Type::RegionLandOfShadowUp_DealWithEvil:
        return tr("Remove your control token from any province other than the Shadowlands. "
                  "Then select 4 or fewer battle tokens on the board and look "
                  "at their faces without showing the others. "
                  "Reveal one of these tokens and send it to its clan's discard.");
    case Type::RegionLandOfShadowUp_KillingTheWeak:
        return tr("Discard a Battle token from your asset. You do not place "
                  "a battle token this turn. Then reveal any 2 battle tokens on the board "
                  "and send them to their clans' discard.");

    case Type::RegionLion_Bushido:
        return tr("Select a province (except the Shadowlands) and place "
                  "a 4-flower token in it, covering the flower printed on the board. "
                  "The honor value of this province becomes 4.");
    case Type::RegionLion_GloriousBattle:
        return tr("Select a province and place a Glory token on it. "
                  "Diplomacy and mayhem tokens cannot be placed in this province.");

    case Type::RegionPhoenix_KamiSupport:
        return tr("Select a province (except Shadowlands) "
                  "and place a +2 Defense Bonus token there.");
    case Type::RegionPhoenix_Purge:
        return tr("Remove the Scorched Earth token from any province. Then, place 2 "
                  "of your control tokens in that province and turn one of them face up.");

    case Type::RegionScorpion_FiresOfRebellion:
        return tr("Remove a peace token from any province. If you control this province, "
                  "place 2 control tokens faceup on it.");
    case Type::RegionScorpion_SpyNetwork:
        return tr("Choose another player and see the tokens in his asset. "
                  "This player cannot use an empty token for this round.");

    case Type::RegionUnicorn_CulturalExchange:
        return tr("Choose a province under your control and a province under enemy control. "
                  "Swap all control tokens in your province with all control tokens "
                  "in the enemy province (do not flip them).");
    case Type::RegionUnicorn_Reinforcement:
        return tr("Choose 2 Army tokens from your discard and return them to your asset. "
                  "Then choose 2 battle tokens from your asset and either discard them "
                  "or mix them into your personal supply.");
    default:;
    }
    return "";
}

BattleForRokugan::Card::Type BattleForRokugan::Card::type() const
{
    return m_type;
}

bool BattleForRokugan::Card::isUsed() const
{
    return m_used;
}

void BattleForRokugan::Card::use()
{
    m_used = true;
}

std::array<unsigned, 3> BattleForRokugan::Card::randNeutralCard()
{
    std::array <unsigned, 3> ret = { 0, 0, 0 };
    ret[AFlib::Function::randomInt(0, 2)] = 1;
    while (true){
        unsigned i = AFlib::Function::randomInt(0, 2);
        if (ret[i] == 0){
            ret[i] = 2;
            break;
        }
    }
    return ret;
}

BattleForRokugan::Card::Type BattleForRokugan::Card::getNeutralCard(unsigned i)
{
    return static_cast <Type> (static_cast <unsigned char>(Type::LordOfTheLands) + i);
}

bool BattleForRokugan::Card::isInitiative(BattleForRokugan::Card::Type type)
{
    return type >= Card::Type::FirstInitiative && type <= Card::Type::LastInitiative;
}

bool BattleForRokugan::Card::isRegion(BattleForRokugan::Card::Type type)
{
    return type >= Card::Type::FirstRegion && type <= Card::Type::LastRegion;
}

BattleForRokugan::Card::Type operator+(BattleForRokugan::Card::Type type, unsigned i)
{
    using namespace BattleForRokugan;
    return static_cast <Card::Type>(static_cast <unsigned>(type) + i);
}

BattleForRokugan::Card::Type operator-(BattleForRokugan::Card::Type l, BattleForRokugan::Card::Type r)
{
    using namespace BattleForRokugan;
    return static_cast <Card::Type>(static_cast <int>(l) -static_cast <int>(r));
}

BattleForRokugan::Card::Type operator+(BattleForRokugan::Card::Type card, BattleForRokugan::Clan::Type clan)
{
    using namespace BattleForRokugan;
    return static_cast <Card::Type>(static_cast <unsigned>(card) +
                                    static_cast <unsigned>(clan));
}
