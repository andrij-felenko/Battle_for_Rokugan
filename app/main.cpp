#include <AFquick/AfGuiApplication>
#include <TrinnGui>
#include <QtGui/QIcon>
#include <QDir>
#include "AFbaseLib"
#include "lib_bfr/mission.h"

int main(int argc, char** argv)
{
    AFquick::GuiApplication app(argc, argv);

    Q_INIT_RESOURCE(rc_af_base);
//    Q_INIT_RESOURCE(rc_business);
//    Q_INIT_RESOURCE(rc_material_design);

    Q_INIT_RESOURCE(af_quick_rc);

    // TODO add company information
    app.setWindowIcon(QIcon(":/icon/af_base/af_logo.svg"));
    BattleForRokugan::Mission m;
    qDebug() << m.description(BattleForRokugan::Mission::Type::EmeraldEmpire);

    return app.exec();
}
