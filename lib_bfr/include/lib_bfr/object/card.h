#ifndef LIB_BFR_OBJECT_CARD_H
#define LIB_BFR_OBJECT_CARD_H

#include "bfrLib_pre.h"

class battle_for_rokugan::object::Card : public QObject
{
    Q_OBJECT
public:
    Card(CardType type, Player* owner = nullptr);
    Q_ENUM(CardType)

    QString name() const;
    QString description() const;
    CardType type() const;

    bool isUsed() const;

    static array_u3 randNeutralCard();
    static CardType getNeutralCard(uint i);

    static bool isInitiative(CardType type);
    static bool isTerritory(CardType type);

    Player *getOwner() const;
    void setOwner(Player *owner);

public slots:
    CombatTokenType useFirstPlayer(token::Combat* token);
    CombatTokenType useScout(token::Combat* token);
    void useShugenja(token::Combat* token);

    // territory side
    void useTerritoryCrab_Promotion(karta::Province* province);
    void useTerritoryCrab_FeatsOfEngineering(karta::Province* province,
                                             karta::Province* pushProvince = nullptr);

    void useTerritoryCrane_CodeOfHonor(karta::Province* prov1,
                                       karta::Province* prov2);
    void useTerritoryCrane_DiplomaticMission(karta::Province* provPeace,
                                             karta::Province* provToken = nullptr);

    void useTerritoryDragon_SacredGround(karta::Province* province);
    void useTerritoryDragon_StrengthOfPurpose(karta::Province* prov1,
                                              karta::Province* prov2);

    void useTerritoryIslands_PortOfProsperity(karta::Province* province);
    void useTerritoryIslands_PirateRaids(karta::Province* provScorch,
                                         karta::Province* provToken = nullptr);

    void useTerritoryLion_Bushido(karta::Province* province);
    void useTerritoryLion_HonorableFight(karta::Province* province);

    void useTerritoryMountains_BountifulHarvest(karta::Province* province);
    void useTerritoryMountains_AshigaruLevies(karta::Province* prov1,
                                              karta::Province* prov2,
                                              karta::Province* prov3);

    void useTerritoryPhoenix_AidOfTheKami(karta::Province* province);
    void useTerritoryPhoenix_BlessTheLands(karta::Province* province);

    void useTerritoryScorpion_FomentRebellion(karta::Province* province);

    void useTerritoryShadowlandsSouth_InspireFear(karta::Province* province,
                                                  token::Province* token1,
                                                  token::Province* token2 = nullptr);

    void useTerritoryUnicorn_Reinforcement(token::Combat* dis1, token::Combat* dis2,
                                           token::Combat* ast1, token::Combat* ast2);
    void useTerritoryUnicorn_CulturalExchange(karta::Province* prov1,
                                              karta::Province* prov2);

private:
    Player* m_owner;
    CardType m_type;
    bool m_used;
    void use();

//    void useTerritoryScorpion_SpyNetwork:        return tr("Spy Network");
//    void useTerritoryShadowlandsNorth_DarkFavors:     return tr("Dark favors");
//    void useTerritoryShadowlandsNorth_PurgeTheWeak:   return tr("Purge the weak");
//    void useTerritoryShadowlandsSouth_AnimateTheDead: return tr("Animate the dead");

    friend class handler::Turn;
};

namespace battle_for_rokugan {
    CardType operator+ (CardType type, uint i);
    CardType operator+ (CardType card, ClanType clan);
    CardType operator- (CardType left, CardType right);
}

#endif
