#ifndef LIB_BFR_PLAYER_H
#define LIB_BFR_PLAYER_H

#include "bfrLib_pre.h"

class BattleForRokugan::Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name, ClanType clan, Map* map, ClanStats* stats,
           Mission* mis1, Mission* mis2, QObject* parent);
    virtual ~Player();

    QString name() const;
    const Clan* clan() const;
    const Mission* mission() const;

    ErrorMsg pickMission(MissionType mission);
    unsigned regionCardCount() const;
    unsigned provinceCount() const;
    unsigned controlTokenCount() const;
    unsigned pointsOfHonor() const;

    void   takeProvince(Province* province);
    void untakeProvince(Province* province);
    void lostProvince(Province* province);
    void lostProvince(Player* player);

    int position() const;
    void setPosition(int position);

    int queue() const;
    void setQueue(int queue);

    bool contains(MissionType type) const;

    void    addFirstCard(Card* firstCard);
    void removeFirstCard();
    void setStartCtrlToken(int size);

signals:
    void missionPicked();
    void startCtrlTokenPlaced();
    void battleTokenPlaced();

private:
    Clan* m_clan;
    QString m_name;
    Mission* m_mission1;
    Mission* m_mission2;
    Map* m_map;
    ClanStats* m_stats;
    int m_position;
    int m_queue;
    int m_startCtrlToken;

    ProvinceList m_provinceList;

    CardList m_cardList;
    TurnTokenList m_tokenDischargeList;
    TurnTokenList m_tokenReserveList;
    TurnTokenList m_tokenAssetsList;
    inline void addTokenToReserve(TurnTokenType type,
                                  unsigned char count = 1,
                                  unsigned char value = 0);
};

#endif // LIB_BFR_PLAYER_H
