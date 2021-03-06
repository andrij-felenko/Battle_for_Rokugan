#ifndef LIB_BFR_LIB_ENUM_H
#define LIB_BFR_LIB_ENUM_H
#include <optional>
#include <QtCore/QList>

namespace BattleForRokugan {
//!
//! \brief The BorderType enum
//!
enum class BorderType {
    Land,
    Navy,
};

//!
//! \brief The CardType enum
//!
enum class CardType {
    FirstPlayer,       ///< [1]
    Shugendja,         ///< [5]
    Intelligence,      ///< [10]
    InitiativeCrab,    ///< [7 for each nation with their logit and 3 neutral cards]
    InitiativeCrane,
    InitiativeDragon,
    InitiativeLion,
    InitiativePhoenix,
    InitiativeScorpion,
    InitiativeUnicorn,
    LordOfTheLands,       ///< Neutral card
    SupremeStrategist,    ///< Neutral card
    YoungEmperor,         ///< Neutral card
    RegionCrab_SeaAccess, ///< region cards
    RegionCrab_Castling,
    RegionCrane_CodeOfHonor,
    RegionCrane_DiplomaticMission,
    RegionDragon_ObjectiveMovement,
    RegionDragon_BlessedLand,
    RegionLion_Bushido,
    RegionLion_GloriousBattle,
    RegionPhoenix_KamiSupport,
    RegionPhoenix_Purge,
    RegionScorpion_SpyNetwork,
    RegionScorpion_FiresOfRebellion,
    RegionUnicorn_Reinforcement,
    RegionUnicorn_CulturalExchange,
    RegionArchipelago_PirateRaids,
    RegionArchipelago_Prosperity,
    RegionDune_BountifulHarvest,
    RegionDune_AshigaruMilitia,
    RegionLandOfShadowUp_DealWithEvil,
    RegionLandOfShadowUp_KillingTheWeak,
    RegionLandOfShadowDown_RaiseDead,
    RegionLandOfShadowDown_DominionOfTerror,

    FirstInitiative = InitiativeCrab,
    LastInitiative = InitiativeUnicorn,

    FirstRegion = RegionCrab_SeaAccess,
    LastRegion = RegionLandOfShadowDown_DominionOfTerror,
};
typedef QList <CardType> CardTypeList;

//!
//! \brief The ClanType enum
//!
enum class ClanType {
    Crab,
    Crane,
    Dragon,
    Lion,
    Phoenix,
    Scorpion,
    Unicorn,
    None,
    First = Crab
};
typedef std::optional <ClanType> ClanTypeOpt;
typedef QList <ClanType> ClanTypeList;

//!
//! \brief The PlaceType enum
//!
enum class PlaceType{
    //
};

//!
//! \brief The Phase enum
//!
enum class Phase : unsigned char {
    Pregame,
    Game,
    Postgame
};

//!
//! \brief The MissionType enum
//!
enum class MissionType : unsigned char {
    SuburbOfTheFiveWinds = 0,
    GreatLibrary,
    VaultOfSecrets,
    EmpireRiceBowl,
    GreatWallOfTheNorth,
    MasterOfTheSeas,
    EmeraldEmpire,
    Modesty_PolitenessOfKings,
    UbiquitousInfluence,
    Battlefield,
    TheLastLineOfDefense,
    ForgottenLands,

    First = SuburbOfTheFiveWinds,
    Last = ForgottenLands
};

//!
//! \brief The ProvinceTokenType enum
//!
enum class ProvinceTokenType {
    Shrine, ///< [ 1]
    Harbor, ///< [ 1]
    Glory,  ///< [ 1]
    Peace,  ///< [15]
    ScorchedEarth,   ///< [15]
    ProtectionBonus, ///< [ 4]
    HonorBonus,      ///< [ 4]
    ControlOn, ///< [27], on first 2[11], 3[7], 4[5], 5[4]
    ControlOff
};

//!
//! \brief The RegionType enum
//!
enum class RegionType : uchar {
    Crab,
    Crane,
    Dragon,
    Lion,
    Phoenix,
    Scorpion,
    Unicorn,
    Archipelago,
    Dune,
    ShadowUp,
    ShadowDown,
    None,

    First = Crab,
    Last = ShadowDown,
};

//!
//! \brief The TurnTokenType enum
//!
enum class TurnTokenType {
    Army,    ///< 1[6], 2[4], 3[3], 4[2], 5[1]
    Navy,    ///< 1[2], 2[1]
    Shinobi, ///< 1[1], 2[2]
    Diplomacy, ///< 1[1]
    Sabotage,  ///< 1[1]
    Blessing,  ///< 2[2]
    Empty,  ///< [ 1]
    None,
};

typedef TurnTokenType TTT;

//!
//! \brief The TurnTokenStatus enum
//!
enum class TurnTokenStatus {
    Reserve,
    Assets,
    Discharge
};
typedef TurnTokenStatus TTS;
}

#endif // LIB_BFR_LIB_ENUM_H
