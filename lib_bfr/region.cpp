#include "lib_bfr/region.h"
#include "lib_bfr/province.h"
#include <AfFunction>

BFR::Region::Region(RegionType type, QObject *parent)
    : QObject(parent), m_type(type), m_firstCard(AFfunction::randomInt(0, 1))
{
    // init provinces
    switch (type) {
    case RegionType::Crab:       addProvinces({ 1, 3, 2, 2 },  3, {          3 }); break;
    case RegionType::Crane:      addProvinces({ 2, 2, 3    },  0, { 0, 1, 2    }); break;
    case RegionType::Dragon:     addProvinces({ 1, 2, 3    },  1                ); break;
    case RegionType::Lion:       addProvinces({ 2, 2, 2    },  1 ,{       2    }); break;
    case RegionType::Phoenix:    addProvinces({ 2, 2, 1    },  0, {       2    }); break;
    case RegionType::Scorpion:   addProvinces({ 3, 2, 1    },  1                ); break;
    case RegionType::Unicorn:    addProvinces({ 2, 3, 1    },  0                ); break;
    case RegionType::Archipelago:addProvinces({ 2, 1, 1    }, -1, { 0, 1, 2    }); break;
    case RegionType::Dune:       addProvinces({ 3, 2, 3    }, -1, {    1, 2    }); break;
    case RegionType::ShadowDown: addProvinces({ 0          }, -1, { 0          }); break;
    case RegionType::ShadowUp:   addProvinces({ 0          }                    ); break;
    default:;
    }
}

BFR::ClanType BFR::Region::daimyo() const
{
    auto clan = ClanType::None;
    for (const auto &it : m_provinceList){
        if (it->scorched())
            continue;

        if (it->clanType() == ClanType::None)
            return ClanType::None;

        if (clan == ClanType::None){
            clan = it->clanType();
            continue;
        }

        if (it->clanType() == clan)
            continue;

        return ClanType::None;
    }

    return clan;
}

int BFR::Region::provinceOwnerCount(ClanType type) const
{
    int ret = 0;
    for (const auto &it : m_provinceList)
        if (it->clanType() == type)
            ret++;
    return ret;
}

BFR::Province* BFR::Region::capital() const
{
    for (auto it : m_provinceList)
        if (it->capital())
            return it;
    return nullptr;
}

BFR::Province* BFR::Region::operator[](unsigned number) const
{
    if (number < 0 || number >= m_provinceList.size())
        return nullptr;
    return m_provinceList[number];
}

BFR::RegionType BFR::Region::type() const
{
    return m_type;
}

bool BFR::Region::isShadow(RegionType type)
{
    return type == RegionType::ShadowDown || type == RegionType::ShadowUp;
}

uint BFR::Region::provinceCount() const
{
    return m_provinceList.size();
}

void BFR::Region::addProvinces(char_v list, char capital, char_v navyList)
{
    if (list.size() <= 0)
        return;

    for (char i = 0; i < char(list.size()); i++){
        bool navy = std::find(navyList.begin(), navyList.end(), i) != navyList.end();
        m_provinceList.push_back(new Province(m_type, i == capital, navy, i, list[i], this));
    }
}

BFR::Province* BFR::Region::findProvince(uchar number)
{
    for (auto it : m_provinceList)
        if (it->number() == number)
            return it;
    return nullptr;
}

namespace BattleForRokugan {
    RegionType operator+(RegionType type, unsigned i)
    {
        return static_cast <RegionType>(static_cast <uint>(type) + i);
    }

    RegionType operator++(RegionType type)
    {
        return type + 1;
    }
}
