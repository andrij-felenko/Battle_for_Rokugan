#ifndef LIB_BFR_PLAYER_H
#define LIB_BFR_PLAYER_H

#include <QtCore/QObject>
#include "card.h"
#include "clan.h"
#include "mission.h"
#include "turnToken.h"
#include "province.h"

namespace BattleForRokugan {
    class Player;
}

class BattleForRokugan::Player : public QObject
{
    Q_OBJECT
public:
    Player(QString name, Clan::Type type, QObject* parent = nullptr);

    QString name() const;
    const Clan* clan() const;
    const Mission* mission() const;

    void setMission(Mission::Type mission);
    unsigned regionCardCount() const;
    unsigned provinceCount() const;
    unsigned controlTokenCount() const;

private:
    Clan* m_clan;
    QString m_name;
    Mission* m_mission;

    std::list <std::shared_ptr <Province>> m_provinceList;

    QList <Card*> m_cardList;
    QList <TurnToken*> m_tokenDischargeList;
    QList <TurnToken*> m_tokenReserveList;
    QList <TurnToken*> m_tokenAssetsList;
    inline void addTokenToReserve(TurnToken::Type type, unsigned char count = 1,
                                  unsigned char value = 0);
};

#endif // LIB_BFR_PLAYER_H
