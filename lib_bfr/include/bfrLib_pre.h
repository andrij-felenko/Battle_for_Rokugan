#ifndef LIB_BFR_LIB_PRE_H
#define LIB_BFR_LIB_PRE_H

#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#include <vector>
#include "bfrEnum.h"

#define AFdeclareClass(name) \
    class name; \
    typedef QList <name*> name##List;

typedef std::array <unsigned, 3> array_u3;
typedef std::array <unsigned, 7> array_u7;

typedef std::optional <QString> ErrorMsg;
typedef std::vector < char>  char_v;
typedef std::vector <uchar> uchar_v;
typedef std::vector <std::pair <uchar, uchar>> uchar_pair_v;

namespace battle_for_rokugan {
    AFdeclareClass(Game)

namespace handler {
    AFdeclareClass(Battle)
    AFdeclareClass(Stats)
    AFdeclareClass(Turn)
}

namespace karta {
    AFdeclareClass(Border)
    AFdeclareClass(Map)
    AFdeclareClass(Province)
    AFdeclareClass(Territory)
    AFdeclareClass(TokenBasement)
}

namespace object {
    AFdeclareClass(Card)
    AFdeclareClass(Clan)
    AFdeclareClass(Player)
    AFdeclareClass(SecretObjective)
}

namespace token {
    AFdeclareClass(Combat)
    AFdeclareClass(Control)
    AFdeclareClass(Honor)
    AFdeclareClass(Province)
}
}

namespace bfr = battle_for_rokugan;

#endif // LIB_BFR_LIB_PRE_H
