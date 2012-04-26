#include <QtGui>
#include <QInputDialog>
#include "FenPrincipale.h"
#include "Line.h"
#include "serial.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);


    //------------------------------------------------------------------------------


    int port = QInputDialog::getInt(NULL,"Choose the COM port","Please choose the serial communication port to get important informations :",1);
    Serial* com = new Serial(port);

    //com->start();

    //------------------------------------------------------------------------------

    FenPrincipale w(com);
    w.show();

    //------------------------------------------------------------------------------

    Line* n = new Line();

        n->altitude = 2.2;
        n->CH4 = 3;
        n->CO2 = 89;
        n->gpsaltitude = 6;
        n->gpsx = 4;
        n->gpsy = 121;
        n->GyrX = 89;
        n->GyrY = 90;
        n->GyrZ = 91;
        n->hyg = 88989;
        n->pressin = 100;
        n->pressout = 200;
        n->temphyg = 67;
        n->tempin = 28;
        n->tempout = 27;
        n->vith = 100;
        n->vitv = 101;

    w.append(n);

    return a.exec();
}
