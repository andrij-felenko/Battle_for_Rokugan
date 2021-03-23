#ifndef LIB_BFR_KARTA_MAP_H
#define LIB_BFR_KARTA_MAP_H

#include "bfrLib_pre.h"
#include <array>

class battle_for_rokugan::karta::Map : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showCombatToken READ showCombatToken NOTIFY showCombatTokenChanged)
public:
    Map(QObject* parent);

    Territory* operator[](const TerritoryType type) const;
    void clear();
    void openTokens();
    void newTurn();

    bool showCombatToken() const;

signals:
    void allTokenOpened();
    void showCombatTokenChanged(bool showCombatToken);

private:
    TerritoryList m_territoryList;
    BorderList m_listBorders;
    bool m_showCombatToken;

    inline bool addBorder(TerritoryType type, uchar_v v);
    inline bool addBorder(TerritoryType type1, unsigned char s1,
                          TerritoryType type2, unsigned char s2 = 0);
    inline bool addBorder(TerritoryType type1, uchar_v s1,
                          TerritoryType type2, uchar_v s2);
    inline bool addBorder(TerritoryType type, uchar_pair_v v);
    inline bool addBorder(TerritoryType type1, TerritoryType type2, uchar_pair_v v);

    Province*  findProvince(TerritoryType type, unsigned char stars) const;
    Territory* findTerritory  (TerritoryType type) const;

    inline void addLandBorder();
    inline void addNavyBorder();

    void setShowCombatToken(bool showCombatToken);

    friend class Game;
    friend class handler::Battle;
    friend class object::SecretObjective;
};

#endif
