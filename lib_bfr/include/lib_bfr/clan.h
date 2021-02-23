#ifndef LIB_BFR_CLAN_H
#define LIB_BFR_CLAN_H

#include "bfrLib_pre.h"

class BattleForRokugan::Clan : public QObject
{
    Q_OBJECT
public:    
    Clan(ClanType type, QObject* parent);
    Q_ENUM(ClanType)

    ClanType type() const;
    void setType(ClanType type);

    static RegionType homeRegion(ClanType type);
    RegionType homeRegion() const;

    static QString name(ClanType type);
    QString name() const;

    const TurnToken* specialClanToken() const;

private:
    ClanType m_type;
    TurnToken* m_specialToken;
};

namespace BattleForRokugan {
    ClanType operator+(ClanType type, uint i);
}

#endif // LIB_BFR_CLAN_H
