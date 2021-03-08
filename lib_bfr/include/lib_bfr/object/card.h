#ifndef LIB_BFR_OBJECT_CARD_H
#define LIB_BFR_OBJECT_CARD_H

#include "bfrLib_pre.h"

class BattleForRokugan::Object::Card : public QObject
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
    CombatTokenType useFirstPlayer(Token::Combat* token);
    CombatTokenType useScout(Token::Combat* token);
    void useShugenja(Token::Combat* token);

    // territory side
    void useTerritoryCrab_Promotion(Karta::Province* province);
    void useTerritoryCrab_FeatsOfEngineering(Karta::Province* province,
                                             Karta::Province* pushProvince = nullptr);

    void useTerritoryCrane_CodeOfHonor(Karta::Province* prov1,
                                       Karta::Province* prov2);
    void useTerritoryCrane_DiplomaticMission(Karta::Province* provPeace,
                                             Karta::Province* provToken = nullptr);

    void useTerritoryDragon_SacredGround(Karta::Province* province);
    void useTerritoryDragon_StrengthOfPurpose(Karta::Province* prov1,
                                              Karta::Province* prov2);

    void useTerritoryIslands_PortOfProsperity(Karta::Province* province);
    void useTerritoryIslands_PirateRaids(Karta::Province* provScorch,
                                         Karta::Province* provToken = nullptr);

    void useTerritoryLion_Bushido(Karta::Province* province);
    void useTerritoryLion_HonorableFight(Karta::Province* province);

    void useTerritoryMountains_BountifulHarvest(Karta::Province* province);
    void useTerritoryMountains_AshigaruLevies(Karta::Province* prov1,
                                              Karta::Province* prov2,
                                              Karta::Province* prov3);

    void useTerritoryPhoenix_AidOfTheKami(Karta::Province* province);
    void useTerritoryPhoenix_BlessTheLands(Karta::Province* province);

    void useTerritoryScorpion_FomentRebellion(Karta::Province* province);

    void useTerritoryShadowlandsSouth_InspireFear(Karta::Province* province,
                                                  Token::Province* token1,
                                                  Token::Province* token2 = nullptr);

    void useTerritoryUnicorn_Reinforcement(Token::Combat* dis1, Token::Combat* dis2,
                                           Token::Combat* ast1, Token::Combat* ast2);
    void useTerritoryUnicorn_CulturalExchange(Karta::Province* prov1,
                                              Karta::Province* prov2);

private:
    Player* m_owner;
    CardType m_type;
    bool m_used;
    void use();

//    void useTerritoryScorpion_SpyNetwork:        return tr("Spy Network");
//    void useTerritoryShadowlandsNorth_DarkFavors:     return tr("Dark favors");
//    void useTerritoryShadowlandsNorth_PurgeTheWeak:   return tr("Purge the weak");
//    void useTerritoryShadowlandsSouth_AnimateTheDead: return tr("Animate the dead");

    friend class Handler::Turn;
};

namespace BattleForRokugan {
    CardType operator+ (CardType type, uint i);
    CardType operator+ (CardType card, ClanType clan);
    CardType operator- (CardType left, CardType right);
}

#endif
