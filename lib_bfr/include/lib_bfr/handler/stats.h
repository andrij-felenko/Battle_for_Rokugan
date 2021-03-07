#ifndef LIB_BFR_HANDLER_STATS_H
#define LIB_BFR_HANDLER_STATS_H

#include "bfrLib_pre.h"

class BattleForRokugan::Handler::Stats : public QObject
{
    Q_OBJECT
public:
    class OneStat;
    typedef std::optional <OneStat*> OneStatOpt;

    Stats(Karta::Map* map);
    virtual ~Stats();

    OneStatOpt operator[](ClanType clan) const;

    ClanTypeList maxRegionCard() const;
    ClanTypeList minProvinceClan() const;
    ClanTypeList maxProvinceClan() const;
    ClanTypeList maxCtrlToken(bool withToken) const;
    bool maxProvinceClan(ClanType clan) const;
    bool minProvinceClan(ClanType clan) const;

    void update();
    void clear();

private:
    Karta::Map* m_map;
    QList <OneStat*> m_clanList;
};

class BattleForRokugan::Handler::Stats::OneStat : public QObject
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

    Q_PROPERTY(uint regionCount
               READ     regionCount
               WRITE setRegionCount
               NOTIFY   regionCountChanged)

    Q_PROPERTY(uint regionCardCount
               READ     regionCardCount
               WRITE setRegionCardCount
               NOTIFY   regionCardCountChanged)

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
    uint regionCount()     const;
    uint regionCardCount() const;
    uint ctrlTokenOn()     const;
    uint ctrlTokenOff()    const;
    uint ctrlToken()       const;
    ClanType type()        const;

signals:
    void honorPointsChanged    (uint honorPoints);
    void provinceCountChanged  (uint provinceCount);
    void regionCountChanged    (uint regionCount);
    void regionCardCountChanged(uint regionCardCount);
    void ctrlTokenOnChanged    (uint ctrlTokenOn);
    void ctrlTokenOffChanged   (uint ctrlTokenOff);
    void ctrlTokenChanged      (uint ctrlToken);
    void typeChanged           (ClanType type);

private:
    friend class Stats;
    uint m_honorPoints;
    uint m_provinceCount;
    uint m_regionCount;
    uint m_regionCardCount;
    uint m_ctrlTokenOn;
    uint m_ctrlTokenOff;
    ClanType m_type;

    void clear();
    void setHonorPoints    (uint honorPoints);
    void setProvinceCount  (uint provinceCount);
    void setRegionCount    (uint regionCount);
    void setRegionCardCount(uint regionCardCount);
    void setCtrlTokenOn    (uint ctrlTokenOn);
    void setCtrlTokenOff   (uint ctrlTokenOff);
};

#endif
