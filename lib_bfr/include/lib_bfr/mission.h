#ifndef LIB_BFR_MISSION_H
#define LIB_BFR_MISSION_H

#include "bfrLib_pre.h"

class BattleForRokugan::Mission : public QObject
{
    Q_OBJECT
public:
    Mission(MissionType type, Map* map, ClanStats* stats, QObject* parent);
    Q_ENUM(MissionType)

    QString name();
    QString description();

    int result() const;
    static int result(MissionType type, Clan* clan, Map* map, ClanStats* stats);

    QString name() const;
    static QString name(MissionType type);

    QString description() const;
    static QString description(MissionType type);

    MissionType type() const;

    bool picked() const;
    void setPicked(Clan* clan);

private:
    MissionType m_type;
    Clan* m_clan;
    bool m_picked;
    Map* m_map;
    ClanStats* m_stats;
};

namespace BattleForRokugan {
    MissionType operator+ (MissionType type, uint i);
    MissionType operator++(MissionType type);
}

#endif // LIB_BFR_MISSION_H
