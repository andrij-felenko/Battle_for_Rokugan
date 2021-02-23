#ifndef LIB_BFR_BORDER_H
#define LIB_BFR_BORDER_H

#include "bfrLib_pre.h"

class BattleForRokugan::Border : public QObject
{
    Q_OBJECT
public:
    Border(Province* prov, QObject* parent);
    Border(Province* prov1, Province* prov2, QObject* parent);
    Q_ENUM(BorderType)

    BorderType type() const;
    void setType(BorderType type);

    TurnTokenType token() const;
    void setToken(TurnTokenType token);
    void clear();

    Province* province1() const;
    Province* province2() const;

private:
    BorderType m_type;
    Province* m_province1;
    Province* m_province2;
    TurnTokenType m_token;
};

#endif // LIB_BFR_BORDER_H
