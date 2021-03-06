#ifndef LIB_BFR_PROVINCE_TOKEN_H
#define LIB_BFR_PROVINCE_TOKEN_H

#include "bfrLib_pre.h"

class BattleForRokugan::ProvinceToken : public QObject
{
    Q_OBJECT
public:
    ProvinceToken(ProvinceTokenType type, QObject* parent);
    Q_ENUM(ProvinceTokenType)

    static QString name(ProvinceTokenType type);
    QString name() const;

    ProvinceTokenType type() const;

private:
    ProvinceTokenType m_type;
};

#endif // LIB_BFR_PROVINCE_TOKEN_H
