#ifndef LIB_BFR_OBJECT_SECRET_OBJECTIVE_H
#define LIB_BFR_OBJECT_SECRET_OBJECTIVE_H

#include "bfrLib_pre.h"

class BattleForRokugan::Object::SecretObjective : public QObject
{
    Q_OBJECT
public:
    SecretObjective(SecretObjectiveType type, Karta::Map* map,
                    Handler::Stats* stats, QObject* parent);
    Q_ENUM(SecretObjectiveType)

    QString name();
    QString description();

    int result() const;
    static int result(SecretObjectiveType type, Clan* clan,
                      Karta::Map* map, Handler::Stats* stats);

    QString name() const;
    static QString name(SecretObjectiveType type);

    QString description() const;
    static QString description(SecretObjectiveType type);

    SecretObjectiveType type() const;

    bool picked() const;
    void setPicked(Clan* clan);

private:
    SecretObjectiveType m_type;
    Clan* m_clan;
    bool m_picked;
    Karta::Map* m_map;
    Handler::Stats* m_stats;
};

namespace BattleForRokugan {
    SecretObjectiveType operator+ (SecretObjectiveType type, uint i);
    SecretObjectiveType operator++(SecretObjectiveType type);
}

#endif
