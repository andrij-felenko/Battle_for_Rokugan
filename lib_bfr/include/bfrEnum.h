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
    Shugenja,         ///< [5]
    Scout,      ///< [10]

    InitiativeCrab,    ///< [7 for each nation with their logit and 3 neutral cards]
    InitiativeCrane,
    InitiativeDragon,
    InitiativeLion,
    InitiativePhoenix,
    InitiativeScorpion,
    InitiativeUnicorn,

    MasterOfGovernance,       ///< Neutral card
    MasterOfTactics,    ///< Neutral card
    RiseOfAnEmpire,         ///< Neutral card

    TerritoryCrab_FeatsOfEngineering, ///< region cards
    TerritoryCrab_Promotion,
    TerritoryCrane_CodeOfHonor,
    TerritoryCrane_DiplomaticMission,
    TerritoryDragon_StrengthOfPurpose,
    TerritoryDragon_SacredGround,
    TerritoryLion_Bushido,
    TerritoryLion_HonorableFight,
    TerritoryPhoenix_AidOfTheKami,
    TerritoryPhoenix_BlessTheLands,
    TerritoryScorpion_SpyNetwork,
    TerritoryScorpion_FomentRebellion,
    TerritoryUnicorn_Reinforcement,
    TerritoryUnicorn_CulturalExchange,
    TerritoryIslands_PirateRaids,
    TerritoryIslands_PortOfProsperity,
    TerritoryMountains_BountifulHarvest,
    TerritoryMountains_AshigaruLevies,
    TerritoryShadowlandsNorth_DarkFavors,
    TerritoryShadowlandsNorth_PurgeTheWeak,
    TerritoryShadowlandsSouth_AnimateTheDead,
    TerritoryShadowlandsSouth_InspireFear,

    FirstInitiative = InitiativeCrab,
    LastInitiative = InitiativeUnicorn,

    FirstTerritory = TerritoryCrab_FeatsOfEngineering,
    LastTerritory = TerritoryShadowlandsSouth_InspireFear,
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
enum class SecretObjectiveType : unsigned char {
    CourtOfTheFiveWinds = 0,
    GreatLibrary,
    DenOfSecrets,
    RiceBowlOfTheEmpire,
    GreatWallOfTheNorth,
    WayOfTheSail,
    EmeraldEmpire,
    WayOfHumility,
    WebOfInfluence,
    PlainsOfBattle,
    TheLastLineOfDefense,
    ReclaimingLostLands,

    First = CourtOfTheFiveWinds,
    Last = ReclaimingLostLands
};
typedef SecretObjectiveType SOT;

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
    HonorBonus       ///< [ 4]
};

//!
//! \brief The TerritoryType enum
//!
enum class TerritoryType : uchar {
    Crab,
    Crane,
    Dragon,
    Lion,
    Phoenix,
    Scorpion,
    Unicorn,
    Islands,
    Mountains,
    ShadowlandsNorth,
    ShadowlandsSouth,
    None,

    First = Crab,
    Last = ShadowlandsSouth
};

//!
//! \brief The CombatTokenType enum
//!
enum class CombatTokenType {
    Army,      ///< 1[6], 2[4], 3[3], 4[2], 5[1]
    Navy,      ///< 1[2], 2[1]
    Shinobi,   ///< 1[1], 2[2]
    Diplomacy, ///< 1[1]
    Raid,      ///< 1[1]
    Blessing,  ///< 2[2]
    Empty,     ///< [ 1]
    None,
};

typedef CombatTokenType CTT;

//!
//! \brief The StatusTokenType enum
//!
enum class StatusTokenType {
    Reserve,
    Assets,
    Discharge
};
typedef StatusTokenType STT;
}

#endif // LIB_BFR_LIB_ENUM_H
