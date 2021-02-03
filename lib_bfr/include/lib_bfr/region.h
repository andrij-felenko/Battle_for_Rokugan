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
        Crane,
        Dragon,
        Phoenix,
        Scorpion,
        Lion,
        Crab,
        Unicorn,
        Archipelago,
        Dune,
        LandOfShadowUp,
        LandOfShadowDown
    }; Q_ENUM(Type)

    Region(const Type type, QObject* parent = nullptr);
    std::optional <Clan::Type> daimyoRegion() const;

    Type type() const;

    std::optional <QString> cardRegionName() const;
    std::optional <QString> cardRegionDescription() const;

private:
    Type m_type;
    bool m_firstCard;
    std::list <std::shared_ptr <Province>> m_provinceList;

    void addProvinces(std::vector<char> list = { 0 }, char capital = -1);
    std::optional <std::shared_ptr <Province>> findProvince(unsigned char number);

    friend class GameMap;
};

#endif // LIB_BFR_REGION_H
