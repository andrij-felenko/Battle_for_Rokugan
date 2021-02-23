#ifndef LIB_BFR_PROVINCE_TOKEN_H
#define LIB_BFR_PROVINCE_TOKEN_H

#include "bfrLib_pre.h"

class BattleForRokugan::ProvinceToken : public QObject
{
    Q_OBJECT
public:
    ProvinceToken(QObject* parent);
    Q_ENUM(ProvinceTokenType)

    QString name(ProvinceTokenType type) const;
    QString name() const;

    ProvinceTokenType type() const;
    void setType(ProvinceTokenType type);

private:
    ProvinceTokenType m_type;
};

#endif // LIB_BFR_PROVINCE_TOKEN_H
