#ifndef LIB_BFR_CLAN_H
#define LIB_BFR_CLAN_H

namespace BattleForRokugan {
    class Clan;
}

class BattleForRokugan::Clan
{
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Crane,
        Dragon,
        Phoenix,
        Scorpio,
        Lion,
        Crab,
        Unicorn,
        Archipelago,
        Dune,
        LandOfShadowUp,
        LandOfShadowDown
    };

    Clan(const Type& type);

    Type type() const;
    void setType(const Type &type);

private:
    Type m_type;
};

#endif // LIB_BFR_CLAN_H
