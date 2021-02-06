#ifndef LIB_BFR_CARD_H
#define LIB_BFR_CARD_H

#include <QtCore/QObject>
#include <array>
#include "clan.h"

namespace BattleForRokugan {
    class Card;
}

class BattleForRokugan::Card : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
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
    }; Q_ENUM(Type)

    Card(const Type type, QObject* parent = nullptr);

    QString name() const;
    QString description() const;
    Type type() const;

    bool isUsed() const;
    void use();

    static std::array <unsigned, 3> randNeutralCard();
    static Type getNeutralCard(unsigned i);

    static bool isInitiative(Type type);
    static bool isRegion(Type type);

private:
    Type m_type;
    bool m_used;
};

BattleForRokugan::Card::Type operator+(BattleForRokugan::Card::Type type, unsigned i);

BattleForRokugan::Card::Type operator-(BattleForRokugan::Card::Type l,
                                       BattleForRokugan::Card::Type r);

BattleForRokugan::Card::Type operator+(BattleForRokugan::Card::Type card,
                                       BattleForRokugan::Clan::Type clan);

#endif // LIB_BFR_CARD_H
