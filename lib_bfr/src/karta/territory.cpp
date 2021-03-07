#include "lib_bfr/karta/territory.h"
#include "lib_bfr/karta/province.h"
#include <AfFunction>

BFR::Karta::Territory::Territory(TerritoryType type, QObject *parent)
    : QObject(parent), m_type(type), m_firstCard(AFfunction::randomInt(0, 1))
{
    // init provinces
    switch (type) {
    case TerritoryType::Crab:             addProvinces({ 1, 3, 2, 2 },  3, {          3 }); break;
    case TerritoryType::Crane:            addProvinces({ 2, 2, 3    },  0, { 0, 1, 2    }); break;
    case TerritoryType::Dragon:           addProvinces({ 1, 2, 3    },  1                ); break;
    case TerritoryType::Lion:             addProvinces({ 2, 2, 2    },  1 ,{       2    }); break;
    case TerritoryType::Phoenix:          addProvinces({ 2, 2, 1    },  0, {       2    }); break;
    case TerritoryType::Scorpion:         addProvinces({ 3, 2, 1    },  1                ); break;
    case TerritoryType::Unicorn:          addProvinces({ 2, 3, 1    },  0                ); break;
    case TerritoryType::Islands:          addProvinces({ 2, 1, 1    }, -1, { 0, 1, 2    }); break;
    case TerritoryType::Mountains:        addProvinces({ 3, 2, 3    }, -1, {    1, 2    }); break;
    case TerritoryType::ShadowlandsSouth: addProvinces({ 0          }, -1, { 0          }); break;
    case TerritoryType::ShadowlandsNorth: addProvinces({ 0          }                    ); break;
    default:;
    }
}

BFR::ClanType BFR::Karta::Territory::daimyo() const
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

int BFR::Karta::Territory::provinceOwnerCount(ClanType type) const
{
    int ret = 0;
    for (const auto &it : m_provinceList)
        if (it->clanType() == type)
            ret++;
    return ret;
}

BFR::Karta::Province* BFR::Karta::Territory::capital() const
{
    for (auto it : m_provinceList)
        if (it->capital())
            return it;
    return nullptr;
}

BFR::Karta::Province* BFR::Karta::Territory::operator[](unsigned number) const
{
    if (number < 0 || number >= m_provinceList.size())
        return nullptr;
    return m_provinceList[number];
}

BFR::TerritoryType BFR::Karta::Territory::type() const
{
    return m_type;
}

bool BFR::Karta::Territory::isShadow(TerritoryType type)
{
    return type == TerritoryType::ShadowlandsNorth || type == TerritoryType::ShadowlandsSouth;
}

uint BFR::Karta::Territory::provinceCount() const
{
    return m_provinceList.size();
}

void BFR::Karta::Territory::addProvinces(char_v list, char capital, char_v navyList)
{
    if (list.size() <= 0)
        return;

    for (char i = 0; i < char(list.size()); i++){
        bool navy = std::find(navyList.begin(), navyList.end(), i) != navyList.end();
        m_provinceList.push_back(new Province(m_type, i == capital, navy, i, list[i], this));
    }
}

BFR::Karta::Province* BFR::Karta::Territory::findProvince(uchar number)
{
    for (auto it : m_provinceList)
        if (it->number() == number)
            return it;
    return nullptr;
}

namespace BattleForRokugan {
    TerritoryType operator+(TerritoryType type, unsigned i)
    {
        return static_cast <TerritoryType>(static_cast <uint>(type) + i);
    }

    TerritoryType operator++(TerritoryType type)
    {
        return type + 1;
    }
}
