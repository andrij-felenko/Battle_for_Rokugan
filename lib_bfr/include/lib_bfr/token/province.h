#ifndef LIB_BFR_TOKEN_STATUS_H
#define LIB_BFR_TOKEN_STATUS_H

#include "bfrLib_pre.h"

class battle_for_rokugan::token::Province : public QObject
{
    Q_OBJECT
public:
    Province(object::Player* player, karta::Province* province, ProvinceTokenType type);
    Q_ENUM(ProvinceTokenType)

    static QString name(ProvinceTokenType type);
    QString name() const;

    ProvinceTokenType type() const;
    karta::Province* province() const;

private:
    ProvinceTokenType m_type;
    object::Player* m_player;
    karta::Province* m_province;
};

#endif
