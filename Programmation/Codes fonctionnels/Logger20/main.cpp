#include <QtGui>
#include <QInputDialog>
#include <QDebug>

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

    qDebug() << "Test " ;

    int port = QInputDialog::getInt(NULL,"Choose the COM port","Please choose the serial communication port to get important informations :",1);



    Serial* com = new Serial(port);


    com->start();

    qDebug() << "Test 4" ;

    //------------------------------------------------------------------------------

    FenPrincipale w(com);
    w.show();

    //------------------------------------------------------------------------------

    return a.exec();
}
