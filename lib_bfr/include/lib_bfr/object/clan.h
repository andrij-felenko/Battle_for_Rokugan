#ifndef LIB_BFR_OBJECT_CLAN_H
#define LIB_BFR_OBJECT_CLAN_H

#include "bfrLib_pre.h"

class BattleForRokugan::Object::Clan : public QObject
{
    Q_OBJECT
public:    
    Clan(ClanType type, QObject* parent);
    Q_ENUM(ClanType)

    ClanType type() const;
    void setType(ClanType type);

    static TerritoryType homeTerritory(ClanType type);
    TerritoryType homeTerritory() const;

    static QString name(ClanType type);
    QString name() const;

    const Token::Combat* uniqueCombatToken() const;

private:
    ClanType m_type;
    Token::Combat* m_specialToken;
};

namespace BattleForRokugan {
    ClanType operator+(ClanType type, uint i);
}

#endif
