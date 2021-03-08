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

namespace BattleForRokugan {
    AFdeclareClass(Game)

namespace Handler {
    AFdeclareClass(Battle)
    AFdeclareClass(Stats)
    AFdeclareClass(Turn)
}

namespace Karta {
    AFdeclareClass(Border)
    AFdeclareClass(Map)
    AFdeclareClass(Province)
    AFdeclareClass(Territory)
    AFdeclareClass(TokenBasement)
}

namespace Object {
    AFdeclareClass(Card)
    AFdeclareClass(Clan)
    AFdeclareClass(Player)
    AFdeclareClass(SecretObjective)
}

namespace Token {
    AFdeclareClass(Combat)
    AFdeclareClass(Control)
    AFdeclareClass(Honor)
    AFdeclareClass(Province)
}
}

namespace BFR = BattleForRokugan;

#endif // LIB_BFR_LIB_PRE_H
