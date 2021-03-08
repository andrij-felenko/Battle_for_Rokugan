#ifndef LIB_BFR_TOKEN_HONOR_H
#define LIB_BFR_TOKEN_HONOR_H

#include "bfrLib_pre.h"
#include "province.h"

class BattleForRokugan::Token::Honor : public QObject
{
    Q_OBJECT
public:
    Honor(uint value, QObject* parent);

    uint honor() const;

private:
    uint m_value;
};

#endif
