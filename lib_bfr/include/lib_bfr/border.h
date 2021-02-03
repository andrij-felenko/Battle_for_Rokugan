#ifndef LIB_BFR_BORDER_H
#define LIB_BFR_BORDER_H

#include <QtCore/QObject>
#include "province.h"
#include "turnToken.h"

namespace BattleForRokugan {
    class Border;
}

class BattleForRokugan::Border : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Land,
        Navy,
    }; Q_ENUM(Type)

    Border(std::shared_ptr<Province> prov, QObject* parent = nullptr);
    Border(std::shared_ptr<Province> prov1, std::shared_ptr<Province> prov2,
           QObject* parent = nullptr);

    Type type() const;
    void setType(const Type &type);

    TurnToken::Type token() const;
    void setToken(const TurnToken::Type &token);
    void clear();

private:
    Type m_type;
    std::shared_ptr <Province> m_province1;
    std::shared_ptr <Province> m_province2;
    TurnToken::Type m_token;
};

#endif // LIB_BFR_BORDER_H
