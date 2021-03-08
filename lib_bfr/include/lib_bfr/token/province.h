#ifndef LIB_BFR_TOKEN_STATUS_H
#define LIB_BFR_TOKEN_STATUS_H

#include "bfrLib_pre.h"

class BattleForRokugan::Token::Province : public QObject
{
    Q_OBJECT
public:
    Province(Object::Player* player, Karta::Province* province, ProvinceTokenType type);
    Q_ENUM(ProvinceTokenType)

    static QString name(ProvinceTokenType type);
    QString name() const;

    ProvinceTokenType type() const;
    Karta::Province* province() const;

private:
    ProvinceTokenType m_type;
    Object::Player* m_player;
    Karta::Province* m_province;
};

#endif
