#include "lib_bfr/provinceToken.h"

BattleForRokugan::ProvinceToken::ProvinceToken()
{
    //
}

QString BattleForRokugan::ProvinceToken::name(const BattleForRokugan::ProvinceToken::Type &type) const
{
    switch (type) {
    case Type::ControlOn:
    case Type::ControlOff:      return tr("Control");
    case Type::Glory:           return tr("Glory");
    case Type::Harbor:          return tr("Harbor");
    case Type::HonorBonus:      return tr("Honor bonus");
    case Type::Peace:           return tr("Peace");
    case Type::ProtectionBonus: return tr("Protection bonus");
    case Type::ScorchedEarth:   return tr("Scorched earth");
    case Type::Shrine:          return tr("Shrine");
    default:;
    }
    return "";
}

QString BattleForRokugan::ProvinceToken::name() const
{
    return name(m_type);
}

BattleForRokugan::ProvinceToken::Type BattleForRokugan::ProvinceToken::type() const
{
    return m_type;
}

void BattleForRokugan::ProvinceToken::setType(const Type &type)
{
    m_type = type;
}
