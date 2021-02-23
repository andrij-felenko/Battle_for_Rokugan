#ifndef LIB_BFR_LIB_PRE_H
#define LIB_BFR_LIB_PRE_H

#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#include <vector>
#include "bfrEnum.h"

#define AFdeclareClass(name) \
    class name; \
    typedef QList <name*> name##List;

//class name; \
//typedef QSharedPointer <name>      name##Ptr; \
//typedef QList          <name##Ptr> name##List; \
//typedef std::optional  <name##Ptr> name##Opt;   \
//\
//typedef std::shared_ptr <name>         name##StdPtr; \
//typedef std::list       <name##StdPtr> name##StdList; \
//typedef std::optional   <name##StdPtr> name##StdOpt;

typedef std::array <unsigned, 3> array_u3;
typedef std::array <unsigned, 7> array_u7;

typedef std::optional <QString> ErrorMsg;
typedef std::vector < char>  char_v;
typedef std::vector <uchar> uchar_v;
typedef std::vector <std::pair <uchar, uchar>> uchar_pair_v;

namespace BattleForRokugan {
    AFdeclareClass(Border)
    AFdeclareClass(Card)
    AFdeclareClass(Clan)
    AFdeclareClass(Game)
    AFdeclareClass(Map)
    AFdeclareClass(Mission)
    AFdeclareClass(Player)
    AFdeclareClass(Province)
    AFdeclareClass(ProvinceToken)
    AFdeclareClass(Region)
    AFdeclareClass(TurnToken)
    AFdeclareClass(Battle)
    AFdeclareClass(ClanStats)
}

namespace BFR = BattleForRokugan;

#endif // LIB_BFR_LIB_PRE_H
