#ifndef LIB_BFR_REGION_H
#define LIB_BFR_REGION_H

#include <list>
#include <memory>
#include <optional>
#include "clan.h"
#include <QtCore/QObject>

namespace BattleForRokugan {
    class Region;
    class Province;
}

class BattleForRokugan::Region : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type : unsigned char {
        Crab,
        Crane,
        Dragon,
        Lion,
        Phoenix,
        Scorpion,
        Unicorn,
        Archipelago,
        Dune,
        ShadowUp,
        ShadowDown
    }; Q_ENUM(Type)

    Region(const Type type, QObject* parent = nullptr);
    std::optional <Clan::Type> daimyoRegion() const;
    int provinceOwnerCount(const Clan::Type type) const;
    std::optional <std::shared_ptr <Province>> capital() const;

    std::shared_ptr <Province> operator[](unsigned number) const;

    Type type() const;

    static bool isShadow(const Type type);

private:
    Type m_type;
    bool m_firstCard;
    std::vector <std::shared_ptr <Province>> m_provinceList;

    void addProvinces(std::vector<char> list, char capital = -1,
                      std::vector <char> navyList = {});
    std::optional <std::shared_ptr <Province>> findProvince(unsigned char number);

    friend class GameMap;
    friend class Mission;
};

#endif // LIB_BFR_REGION_H
