#include <AFquick/AfGuiApplication>
#include <TrinnGui>
#include <QtGui/QIcon>
#include <QDir>
#include "AFbaseLib"

int main(int argc, char** argv)
{
    AFquick::GuiApplication app(argc, argv);

    Q_INIT_RESOURCE(rc_af_base);
    Q_INIT_RESOURCE(rc_business);
    Q_INIT_RESOURCE(rc_material_design);

    Q_INIT_RESOURCE(af_quick_rc);

    // TODO add company information
    app.setWindowIcon(QIcon(":/icon/af_base/af_logo.svg"));


//    app.setAFaccountFlag(true);

    // Trinn
    Q_INIT_RESOURCE(pocket_munnin);
    Q_INIT_RESOURCE(trinn_rc);
    app.addPlugin(TrinnPluginPtr::create());

    app.show();
    QDir dir = QDir(":/");
    qDebug() << dir.entryList();
    if (dir.cd("icon"))
        qDebug() << dir.entryList();

    return app.exec();
}
