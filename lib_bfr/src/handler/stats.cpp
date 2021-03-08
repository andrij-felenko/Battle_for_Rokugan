#include "lib_bfr/handler/stats.h"
#include "lib_bfr/karta/map.h"
#include "lib_bfr/object/clan.h"
#include <set>

BFR::Handler::Stats::Stats(Karta::Map* map)
    : QObject(map), m_map(map)
{
    for (uint i = 0; i < 7; i++)
        m_clanList.push_back(new OneStat(ClanType::First + i));
}

BFR::Handler::Stats::~Stats()
{
    for (auto it : m_clanList)
        it->deleteLater();
}

BFR::Handler::Stats::OneStatOpt
BFR::Handler::Stats::operator [](ClanType clan) const
{
    for (auto it : m_clanList)
        if (it->type() == clan)
            return it;
    return std::nullopt;
}

BFR::ClanTypeList BFR::Handler::Stats::maxTerritoryCard() const
{
    uint cardMax = 0;
    for (auto it : m_clanList)
        if (auto count = it->m_territoryCardCount; count >= cardMax)
            cardMax = count;

    ClanTypeList list;
    for (auto it : m_clanList)
        if (it->territoryCardCount() == cardMax)
            list.push_back(it->type());
    return list;
}

BFR::ClanTypeList BFR::Handler::Stats::maxProvinceClan() const
{
    uint provMax = 0;
    for (auto it : m_clanList)
        if (auto count = it->m_provinceCount; count > provMax)
            provMax = count;

    ClanTypeList list;
    for (auto it : m_clanList)
        if (it->provinceCount() == provMax)
            list.push_back(it->type());
    return list;
}

BFR::ClanTypeList BFR::Handler::Stats::minProvinceClan() const
{
    uint provMin = uint(0) - 1;
    for (auto it : m_clanList)
        if (auto count = it->m_provinceCount; count < provMin)
            provMin = count;

    ClanTypeList list;
    for (auto it : m_clanList)
        if (it->provinceCount() == provMin)
            list.push_back(it->type());
    return list;
}

bool BFR::Handler::Stats::maxProvinceClan(ClanType clan) const
{
    uint provMax = 0;
    for (auto it : m_clanList)
        if (auto count = it->m_provinceCount; count > provMax)
            provMax = count;
    return operator[](clan).value()->provinceCount() == provMax;
}

bool BFR::Handler::Stats::minProvinceClan(ClanType clan) const
{
    uint provMin = uint(0) - 1;
    for (auto it : m_clanList)
        if (auto count = it->m_provinceCount; count < provMin)
            provMin = count;
    return operator[](clan).value()->provinceCount() == provMin;
}

BFR::ClanTypeList BFR::Handler::Stats::maxCtrlToken(bool withToken) const
{
    uint provMax = 0;
    for (auto it : m_clanList)
        if (auto count = withToken ? it->ctrlToken() : it->m_ctrlTokenOff;
                count >= provMax)
            provMax = count;

    ClanTypeList list;
    for (auto it : m_clanList)
        if (auto count = withToken ? it->ctrlToken() : it->m_ctrlTokenOff;
                count == provMax)
            list.push_back(it->type());
    return list;
}

void BFR::Handler::Stats::update()
{
    // TODO
}

void BFR::Handler::Stats::clear()
{
    for (auto it : m_clanList)
        it->clear();
}

typedef BFR::Handler::Stats::OneStat BCO;

BCO::OneStat(ClanType type)
    : m_type(type)
{
    clear();
}

void BCO::clear()
{
    setHonorPoints(0);
    setProvinceCount(0);
    setTerritoryCount(0);
    setTerritoryCardCount(0);
    setCtrlTokenOff(0);
    setCtrlTokenOn(0);
}

BFR::ClanType BCO::type() const { return m_type; }
uint BCO::honorPoints()   const { return m_honorPoints; }
uint BCO::provinceCount() const { return m_provinceCount; }
uint BCO::territoryCount()   const { return m_territoryCount; }
uint BCO::territoryCardCount() const { return m_territoryCardCount; }
uint BCO::ctrlTokenOff() const { return m_ctrlTokenOff; }
uint BCO::ctrlTokenOn() const { return m_ctrlTokenOn; }
uint BCO::ctrlToken()  const { return m_ctrlTokenOff + m_ctrlTokenOn;}

void BCO::setHonorPoints(uint honorPoints)
{
    if (m_honorPoints == honorPoints)
        return;

    m_honorPoints = honorPoints;
    emit honorPointsChanged(m_honorPoints);
}

void BCO::setProvinceCount(uint provinceCount)
{
    if (m_provinceCount == provinceCount)
        return;

    m_provinceCount = provinceCount;
    emit provinceCountChanged(m_provinceCount);
}

void BCO::setTerritoryCount(uint territoryCount)
{
    if (m_territoryCount == territoryCount)
        return;

    m_territoryCount = territoryCount;
    emit territoryCountChanged(m_territoryCount);
}

void BCO::setTerritoryCardCount(uint territoryCardCount)
{
    if (m_territoryCardCount == territoryCardCount)
        return;

    m_territoryCardCount = territoryCardCount;
    emit territoryCardCountChanged(m_territoryCardCount);
}

void BCO::setCtrlTokenOn(uint ctrlTokenOn)
{
    if (m_ctrlTokenOn == ctrlTokenOn)
        return;

    m_ctrlTokenOn = ctrlTokenOn;
    emit ctrlTokenOnChanged(m_ctrlTokenOn);
}

void BCO::setCtrlTokenOff(uint ctrlTokenOff)
{
    if (m_ctrlTokenOff == ctrlTokenOff)
        return;

    m_ctrlTokenOff = ctrlTokenOff;
    emit ctrlTokenOffChanged(m_ctrlTokenOff);
}

