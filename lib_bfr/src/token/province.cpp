#include "lib_bfr/object/player.h"
#include "lib_bfr/token/province.h"

bfr::token::Province::Province(object::Player *player, karta::Province *province, ProvinceTokenType type)
    : QObject(player), m_type(type), m_player(player), m_province(province)
{
    //
}

QString bfr::token::Province::name(ProvinceTokenType type)
{
    switch (type) {
    case ProvinceTokenType::Glory:           return tr("Glory");
    case ProvinceTokenType::Harbor:          return tr("Harbor");
    case ProvinceTokenType::HonorBonusFull:  return tr("Honor bonus");
    case ProvinceTokenType::Peace:           return tr("Peace");
    case ProvinceTokenType::ProtectionBonus: return tr("Protection bonus");
    case ProvinceTokenType::ScorchedEarth:   return tr("Scorched earth");
    case ProvinceTokenType::Shrine:          return tr("Shrine");
    default:;
    }
    return "";
}

QString bfr::token::Province::name() const
{
    return name(m_type);
}

bfr::ProvinceTokenType bfr::token::Province::type() const
{
    return m_type;
}

bfr::karta::Province *bfr::token::Province::province() const
{
    return m_province;
}
