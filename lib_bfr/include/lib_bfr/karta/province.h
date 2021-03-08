#ifndef LIB_BFR_KARTA_PROVINCE_H
#define LIB_BFR_KARTA_PROVINCE_H

#include "bfrLib_pre.h"
#include "tokenBasement.h"

class BattleForRokugan::Karta::Province : public TokenBasement
{
    Q_OBJECT
public:
    Province(TerritoryType territory, bool capital, bool navy,
             uchar number, uchar stars, QObject* parent);

    ClanType clanType() const;
    Object::Player* owner() const;
    void setOwner(Object::Player* newOwner);

    bool scorched() const;
    bool capital() const;
    bool navy() const;
    uchar defends() const;
    uchar number() const;
    uchar stars() const;
    TerritoryType territory() const;

    uchar controlUp() const;

    void addBorder(Border* border);
    ProvinceList neighboringProvinces() const;

    void addControlOnToken(uint count = 1);
    void popControlToken();
    void pushHonor(uint value);
    void setProvinceToken(ProvinceTokenType type);
    void removeProvinceToken(ProvinceTokenType type);

    bool provinceTokenContains(ProvinceTokenType type);
    void clearCombatToken(bool withBorders);

signals:
    void ownerChanged(Object::Player*);
    void scorchedStatusChanged(bool isScorched);
    void ctrlTokenCountChanged();

private:
    bool m_capital;
    bool m_navy;
    uchar m_number;
    uchar m_stars;
    uchar m_defends;

    TerritoryType m_territory;
    Object::Player* m_player;
    Token::ProvinceList m_statusList;
    Token::HonorList m_honorList;
    Token::ControlList m_ctrlTokenList;
    BorderList m_borderList;

    friend class Handler::Battle;
};

#endif
