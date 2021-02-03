#ifndef LIB_BFR_PROVINCE_TOKEN_H
#define LIB_BFR_PROVINCE_TOKEN_H

#include <QtCore/QObject>

namespace BattleForRokugan {
    class ProvinceToken;
}

class BattleForRokugan::ProvinceToken : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Shrine, ///< [ 1]
        Harbor, ///< [ 1]
        Glory,  ///< [ 1]
        Peace,  ///< [15]
        ScorchedEarth,   ///< [15]
        ProtectionBonus, ///< [ 4]
        HonorBonus,      ///< [ 4]
        ControlOn, ///< [27], on first 2[11], 3[7], 4[5], 5[4]
        ControlOff
    }; Q_ENUM(Type)

    ProvinceToken();

    QString name(const Type& type) const;
    QString name() const;

    Type type() const;
    void setType(const Type &type);

private:
    Type m_type;
};

#endif // LIB_BFR_PROVINCE_TOKEN_H
