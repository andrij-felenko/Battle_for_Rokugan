#ifndef LIB_BFR_OBJECT_CARD_H
#define LIB_BFR_OBJECT_CARD_H

#include "bfrLib_pre.h"

class BattleForRokugan::Object::Card : public QObject
{
    Q_OBJECT
public:
    Card(CardType type, Player* owner);
    Q_ENUM(CardType)

    QString name() const;
    QString description() const;
    CardType type() const;

    bool isUsed() const;
    void use();

    static array_u3 randNeutralCard();
    static CardType getNeutralCard(uint i);

    static bool isInitiative(CardType type);
    static bool isTerritory(CardType type);

private:
    Player* m_owner;
    CardType m_type;
    bool m_used;

    CombatTokenType useFirstPlayer(Token::Combat* token);
    CombatTokenType useScout(Token::Combat* token);
    void useShugenja(Token::Combat* token);

    void useTerritoryCrab_FeatsOfEngineering(Karta::Province* province,
                                             Karta::Province* pushProvince = nullptr);
    void useTerritoryCrab_Promotion(Karta::Province* province);
    void useTerritoryCrane_CodeOfHonor(Karta::Province* prov1, Karta::Province* prov2);
    // TODO
//    void useTerritoryCrane_DiplomaticMission:  return tr("Diplomatic Mission");
//    void useTerritoryDragon_SacredGround:      return tr("Sacred ground");
//    void useTerritoryDragon_StrengthOfPurpose: return tr("Strength of purpose");
//    void useTerritoryIslands_PirateRaids:      return tr("Pirate raids");
    void useTerritoryIslands_PortOfProsperity(Karta::Province* province);
//    void useTerritoryLion_Bushido:             return tr("Bushido");
//    void useTerritoryLion_HonorableFight:      return tr("Honorable fight");
//    void useTerritoryMountains_AshigaruLevies:   return tr("Ashigaru levies");
//    void useTerritoryMountains_BountifulHarvest: return tr("Bountiful Harvest");
//    void useTerritoryPhoenix_AidOfTheKami:       return tr("Aid of the Kami");
//    void useTerritoryPhoenix_BlessTheLands:      return tr("Bless the lands");
//    void useTerritoryScorpion_FomentRebellion:   return tr("Foment rebellion");
//    void useTerritoryScorpion_SpyNetwork:        return tr("Spy Network");
//    void useTerritoryShadowlandsNorth_DarkFavors:     return tr("Dark favors");
//    void useTerritoryShadowlandsNorth_PurgeTheWeak:   return tr("Purge the weak");
//    void useTerritoryShadowlandsSouth_AnimateTheDead: return tr("Animate the dead");
    void useTerritoryShadowlandsSouth_InspireFear(Karta::Province* province,
                                                  Token::Province* token1,
                                                  Token::Province* token2 = nullptr);
//    void useTerritoryUnicorn_CulturalExchange: return tr("Cultural Exchange");
    void useTerritoryUnicorn_Reinforcement(Token::Combat* dis1, Token::Combat* dis2,
                                           Token::Combat* ast1, Token::Combat* ast2);

    friend class Handler::Turn;
};

namespace BattleForRokugan {
    CardType operator+ (CardType type, uint i);
    CardType operator+ (CardType card, ClanType clan);
    CardType operator- (CardType left, CardType right);
}

#endif
