#include "lib_bfr/provinceToken.h"

BFR::ProvinceToken::ProvinceToken(ProvinceTokenType type, QObject *parent)
    : QObject(parent), m_type(type)
{
    //
}

QString BFR::ProvinceToken::name(ProvinceTokenType type)
{
    switch (type) {
    case ProvinceTokenType::ControlOn:
    case ProvinceTokenType::ControlOff:      return tr("Control");
    case ProvinceTokenType::Glory:           return tr("Glory");
    case ProvinceTokenType::Harbor:          return tr("Harbor");
    case ProvinceTokenType::HonorBonus:      return tr("Honor bonus");
    case ProvinceTokenType::Peace:           return tr("Peace");
    case ProvinceTokenType::ProtectionBonus: return tr("Protection bonus");
    case ProvinceTokenType::ScorchedEarth:   return tr("Scorched earth");
    case ProvinceTokenType::Shrine:          return tr("Shrine");
    default:;
    }
    return "";
}

QString BattleForRokugan::ProvinceToken::name() const
{
    return name(m_type);
}

BFR::ProvinceTokenType BFR::ProvinceToken::type() const
{
    return m_type;
}
