#include "lib_bfr/object/player.h"
#include "lib_bfr/token/province.h"

BFR::Token::Province::Province(Object::Player *player, ProvinceTokenType type)
    : QObject(player), m_type(type), m_player(player)
{
    //
}

QString BFR::Token::Province::name(ProvinceTokenType type)
{
    switch (type) {
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

QString BattleForRokugan::Token::Province::name() const
{
    return name(m_type);
}

BFR::ProvinceTokenType BFR::Token::Province::type() const
{
    return m_type;
}
