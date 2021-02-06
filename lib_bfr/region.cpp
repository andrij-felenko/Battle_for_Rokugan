#include "lib_bfr/region.h"
#include "lib_bfr/province.h"
#include <QDebug>

BattleForRokugan::Region::Region(const BattleForRokugan::Region::Type type, QObject *parent)
    : QObject(parent), m_type(type), m_firstCard(std::rand()%2)
{
    // init provinces
    switch (type) {
    case Type::Crab:       addProvinces({ 1, 3, 2, 2 },  3, {          3 }); break;
    case Type::Crane:      addProvinces({ 2, 2, 3    },  0, { 0, 1, 2    }); break;
    case Type::Dragon:     addProvinces({ 1, 2, 3    },  1                ); break;
    case Type::Lion:       addProvinces({ 2, 2, 2    },  1 ,{       2    }); break;
    case Type::Phoenix:    addProvinces({ 2, 2, 1    },  0, {       2    }); break;
    case Type::Scorpion:   addProvinces({ 3, 2, 1    },  1                ); break;
    case Type::Unicorn:    addProvinces({ 2, 3, 1    },  0                ); break;
    case Type::Archipelago:addProvinces({ 2, 1, 1    }, -1, { 0, 1, 2    }); break;
    case Type::Dune:       addProvinces({ 3, 2, 3    }, -1, {    1, 2    }); break;
    case Type::ShadowDown: addProvinces({ 0          }, -1, { 0          }); break;
    case Type::ShadowUp:   addProvinces({ 0          }                    ); break;
    default:;
    }
}

std::optional <BattleForRokugan::Clan::Type> BattleForRokugan::Region::daimyoRegion() const
{
    auto clan = Clan::Type::None;
    for (const auto &it : m_provinceList){
        if (auto clanIt = it->clanOwner(); it.get()== m_provinceList.begin()->get()){
            if (clanIt != Clan::Type::None){
                clan = clanIt;
                continue;
            }
            else
                return std::nullopt;
        }
        else if (clanIt != clan)
            return std::nullopt;
    }
    return clan;
}

int BattleForRokugan::Region::provinceOwnerCount(const Clan::Type type) const
{
    int ret = 0;
    for (const auto &it : m_provinceList)
        if (it.get()->clanOwner() == type)
            ret++;
    return ret;
}

std::optional <std::shared_ptr <BattleForRokugan::Province>>
BattleForRokugan::Region::capital() const
{
    for (auto it : m_provinceList)
        if (it.get()->capital())
            return it;
    return std::nullopt;
}

std::shared_ptr <BattleForRokugan::Province>
BattleForRokugan::Region::operator[](unsigned number) const
{
    if (number < 0 || number >= m_provinceList.size())
        return nullptr;
    return m_provinceList[number];
}

BattleForRokugan::Region::Type BattleForRokugan::Region::type() const
{
    return m_type;
}

bool BattleForRokugan::Region::isShadow(const BattleForRokugan::Region::Type type)
{
    return type == Type::ShadowDown || type == Type::ShadowUp;
}

void BattleForRokugan::Region::addProvinces(std::vector <char> list, char capital,
                                            std::vector<char> navyList)
{
    if (list.size() <= 0)
        return;

    for (char i = 0; i < char(list.size()); i++){
        bool navy = std::find(navyList.begin(), navyList.end(), i) != navyList.end();
        m_provinceList.push_back(
                    std::make_shared <Province> (m_type, i == capital, navy, i, list[i]));
    }
}

std::optional <std::shared_ptr <BattleForRokugan::Province>>
BattleForRokugan::Region::findProvince(unsigned char number)
{
    for (auto it : m_provinceList)
        if (it.get()->number() == number)
            return it;
    return std::nullopt;
}
