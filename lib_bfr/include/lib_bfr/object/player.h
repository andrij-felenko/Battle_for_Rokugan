#ifndef LIB_BFR_OBJECT_PLAYER_H
#define LIB_BFR_OBJECT_PLAYER_H

#include "bfrLib_pre.h"

class battle_for_rokugan::object::Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name, ClanType clan, karta::Map* map,
           handler::Turn* turns, handler::Stats* stats,
           SecretObjective* secret1, SecretObjective* secret2, QObject* parent);

    QString name() const;
    const Clan* clan() const;
    const SecretObjective* secretObjective() const;

    ErrorMsg pickSecretObjective(SecretObjectiveType secret);
    unsigned territoryCardCount() const;
    unsigned provinceCount() const;
    unsigned controlTokenCount() const;
    unsigned pointsOfHonor() const;

    void   takeProvince(karta::Province* province);
    void untakeProvince(karta::Province* province);
    void lostProvince(karta::Province* province);
    void lostProvince(Player* player);

    int position() const;
    void setPosition(int position);

    int queue() const;
    void setQueue(int queue);

    bool contains(SecretObjectiveType type) const;

    void    addFirstCard(Card* firstCard);
    void removeFirstCard();
    void setStartCtrlToken(int size);
    void updateCombatTokenInAssets();

signals:
    void secretObjectivePicked();
    void startCtrlTokenPlaced();
    void combatTokenPlaced();

private:
    Clan* m_clan;
    QString m_name;
    SecretObjective* m_secretObjective1;
    SecretObjective* m_secretObjective2;
    karta::Map* m_map;
    handler::Stats* m_stats;
    handler::Turn* m_turns;
    int m_position;
    int m_queue;
    int m_startCtrlToken;

    karta::ProvinceList m_provinceList;

    CardList m_cardList;
    token::CombatList m_tokenList;
    inline void addTokenToReserve(CombatTokenType type,
                                  unsigned char count = 1,
                                  unsigned char value = 0);
};

#endif
