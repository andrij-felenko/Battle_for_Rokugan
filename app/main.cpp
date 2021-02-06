#include <AFquick/AfGuiApplication>
#include <TrinnGui>
#include <QtGui/QIcon>
#include <QDir>
#include "AFbaseLib"
#include "BFRlib"

int main(int argc, char** argv)
{
    AFquick::GuiApplication app(argc, argv);

    Q_INIT_RESOURCE(rc_af_base);
//    Q_INIT_RESOURCE(rc_business);
//    Q_INIT_RESOURCE(rc_material_design);

    Q_INIT_RESOURCE(af_quick_rc);

    // TODO add company information
    app.setWindowIcon(QIcon(":/icon/af_base/af_logo.svg"));

    BattleForRokugan::Game game;
    game.addPlayer("Ja_1");
    game.addPlayer("Ja_2");
    game.addPlayer("Ja_3");
    game.addPlayer("Ja_4");
    game.addPlayer("Ja_5");
    game.start();

    return app.exec();
}
