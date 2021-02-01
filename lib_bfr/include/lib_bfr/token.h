#ifndef LIB_BFR_TOKEN_H
#define LIB_BFR_TOKEN_H

namespace BattleForRokugan {
    class Token;
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Army,    ///< 1[6], 2[4], 3[3], 4[2], 5[1]
        Navy,    ///< 1[2], 2[1]
        Shinobi, ///< 1[1], 2[2]
        Diplomacy, ///< 1[1]
        Sabotage,  ///< 1[1]
        Blessing,  ///< 2[2]
        Empty,  ///< [ 1]
        Shrine, ///< [ 1]
        Harbor, ///< [ 1]
        Glory,  ///< [ 1]
        Peace,  ///< [15]
        ScorchedEarth,   ///< [15]
        ProtectionBonus, ///< [ 4]
        HonorBonus,      ///< [ 4]
        Control, ///< [27], on first 2[11], 3[7], 4[5], 5[4]
    };
}

class BattleForRokugan::Token
{
public:
    Token(const Type& type);

    Type type() const;
    void setType(const Type &type);

private:
    Type m_type;
};

#endif // LIB_BFR_TOKEN_H
