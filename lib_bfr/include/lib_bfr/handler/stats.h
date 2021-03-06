#ifndef LIB_BFR_HANDLER_STATS_H
#define LIB_BFR_HANDLER_STATS_H

#include "bfrLib_pre.h"

class battle_for_rokugan::handler::Stats : public QObject
{
    Q_OBJECT
public:
    class OneStat;
    typedef std::optional <OneStat*> OneStatOpt;

    Stats(karta::Map* map);
    virtual ~Stats();

    OneStatOpt operator[](ClanType clan) const;

    ClanTypeList maxTerritoryCard() const;
    ClanTypeList minProvinceClan() const;
    ClanTypeList maxProvinceClan() const;
    ClanTypeList maxCtrlToken(bool withToken) const;
    bool maxProvinceClan(ClanType clan) const;
    bool minProvinceClan(ClanType clan) const;

    void update();
    void clear();

private:
    karta::Map* m_map;
    QList <OneStat*> m_clanList;
};

class battle_for_rokugan::handler::Stats::OneStat : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint honorPoints
               READ     honorPoints
               WRITE setHonorPoints
               NOTIFY   honorPointsChanged)

    Q_PROPERTY(uint provinceCount
               READ     provinceCount
               WRITE setProvinceCount
               NOTIFY   provinceCountChanged)

    Q_PROPERTY(uint territoryCount
               READ     territoryCount
               WRITE setTerritoryCount
               NOTIFY   territoryCountChanged)

    Q_PROPERTY(uint territoryCardCount
               READ     territoryCardCount
               WRITE setTerritoryCardCount
               NOTIFY   territoryCardCountChanged)

    Q_PROPERTY(uint ctrlTokenOn
               READ     ctrlTokenOn
               WRITE setCtrlTokenOn
               NOTIFY   ctrlTokenOnChanged)

    Q_PROPERTY(uint ctrlTokenOff
               READ     ctrlTokenOff
               WRITE setCtrlTokenOff
               NOTIFY   ctrlTokenOffChanged)

    Q_PROPERTY(uint ctrlToken READ ctrlToken NOTIFY ctrlTokenChanged)
    Q_PROPERTY(ClanType type  READ type      NOTIFY      typeChanged)

public:
    OneStat(ClanType type);

    uint honorPoints()     const;
    uint provinceCount()   const;
    uint territoryCount()     const;
    uint territoryCardCount() const;
    uint ctrlTokenOn()     const;
    uint ctrlTokenOff()    const;
    uint ctrlToken()       const;
    ClanType type()        const;

signals:
    void honorPointsChanged    (uint honorPoints);
    void provinceCountChanged  (uint provinceCount);
    void territoryCountChanged    (uint territoryCount);
    void territoryCardCountChanged(uint territoryCardCount);
    void ctrlTokenOnChanged    (uint ctrlTokenOn);
    void ctrlTokenOffChanged   (uint ctrlTokenOff);
    void ctrlTokenChanged      (uint ctrlToken);
    void typeChanged           (ClanType type);

private:
    friend class Stats;
    uint m_honorPoints;
    uint m_provinceCount;
    uint m_territoryCount;
    uint m_territoryCardCount;
    uint m_ctrlTokenOn;
    uint m_ctrlTokenOff;
    ClanType m_type;

    void clear();
    void setHonorPoints    (uint honorPoints);
    void setProvinceCount  (uint provinceCount);
    void setTerritoryCount    (uint territoryCount);
    void setTerritoryCardCount(uint territoryCardCount);
    void setCtrlTokenOn    (uint ctrlTokenOn);
    void setCtrlTokenOff   (uint ctrlTokenOff);
};

#endif
