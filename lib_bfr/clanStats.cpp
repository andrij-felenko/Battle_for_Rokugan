#include "lib_bfr/clan.h"
#include "lib_bfr/clanStats.h"
#include "lib_bfr/map.h"
#include <set>

BFR::ClanStats::ClanStats(Map* map)
    : QObject(map), m_map(map)
{
    for (uint i = 0; i < 7; i++)
        m_clanList.push_back(new OneClanStat(ClanType::First + i));
}

BFR::ClanStats::~ClanStats()
{
    for (auto it : m_clanList)
        it->deleteLater();
}

BFR::ClanStats::OneClanStatOpt
BFR::ClanStats::operator [](ClanType clan) const
{
    for (auto it : m_clanList)
        if (it->type() == clan)
            return it;
    return std::nullopt;
}

BFR::ClanTypeList BFR::ClanStats::maxRegionCard() const
{
    uint cardMax = 0;
    for (auto it : m_clanList)
        if (auto count = it->m_regionCardCount; count >= cardMax)
            cardMax = count;

    ClanTypeList list;
    for (auto it : m_clanList)
        if (it->regionCardCount() == cardMax)
            list.push_back(it->type());
    return list;
}

BFR::ClanTypeList BFR::ClanStats::minProvinceClan() const
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

bool BFR::ClanStats::minProvinceClan(ClanType clan) const
{
    uint provMin = uint(0) - 1;
    for (auto it : m_clanList)
        if (auto count = it->m_provinceCount; count < provMin)
            provMin = count;
    return operator[](clan).value()->provinceCount() == provMin;
}

BFR::ClanTypeList BFR::ClanStats::maxCtrlToken(bool withToken) const
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

void BFR::ClanStats::update()
{
    // TODO
}

void BFR::ClanStats::clear()
{
    for (auto it : m_clanList)
        it->clear();
}

typedef BFR::ClanStats::OneClanStat BCO;

BCO::OneClanStat(ClanType type)
    : m_type(type)
{
    clear();
}

void BCO::clear()
{
    setHonorPoints(0);
    setProvinceCount(0);
    setRegionCount(0);
    setRegionCardCount(0);
    setCtrlTokenOff(0);
    setCtrlTokenOn(0);
}

BFR::ClanType BCO::type() const { return m_type; }
uint BCO::honorPoints()   const { return m_honorPoints; }
uint BCO::provinceCount() const { return m_provinceCount; }
uint BCO::regionCount()   const { return m_regionCount; }
uint BCO::regionCardCount() const { return m_regionCardCount; }
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

void BCO::setRegionCount(uint regionCount)
{
    if (m_regionCount == regionCount)
        return;

    m_regionCount = regionCount;
    emit regionCountChanged(m_regionCount);
}

void BCO::setRegionCardCount(uint regionCardCount)
{
    if (m_regionCardCount == regionCardCount)
        return;

    m_regionCardCount = regionCardCount;
    emit regionCardCountChanged(m_regionCardCount);
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

