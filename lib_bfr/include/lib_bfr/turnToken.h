#ifndef LIB_BFR_TURN_TOKEN_H
#define LIB_BFR_TURN_TOKEN_H

#include <QtCore/QObject>

namespace BattleForRokugan {
    class TurnToken;
}

class BattleForRokugan::TurnToken : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief The Type enum
    //!
    enum class Type {
        Army,    ///< 1[6], 2[4], 3[3], 4[2], 5[1]
        Navy,    ///< 1[2], 2[1]
        Shinobi, ///< 1[1], 2[2]
        Diplomacy, ///< 1[1]
        Sabotage,  ///< 1[1]
        Blessing,  ///< 2[2]
        Empty,  ///< [ 1]
        None,
    }; Q_ENUM(Type)

    TurnToken(const Type& type, unsigned char value, QObject* parent = nullptr);
    TurnToken(const Type& type, QObject* parent = nullptr);

    Type type() const;
    void setType(const Type &type);

    std::optional <QString> name(const Type& type) const;
    std::optional <QString> name() const;

    unsigned char value() const;
    void setValue(unsigned char value);

private:
    Type m_type;
    unsigned char m_value;
};

#endif // LIB_BFR_TURN_TOKEN_H
