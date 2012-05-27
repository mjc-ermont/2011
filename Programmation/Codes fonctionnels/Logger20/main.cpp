#include <QtGui>
#include <QInputDialog>
#include <QDebug>
#include <ctime>

#include "FenPrincipale.h"
#include "Line.h"
#include "serial.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);


    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);


    //------------------------------------------------------------------------------


    int port = QInputDialog::getInt(NULL,"Choose the COM port","Please choose the serial communication port to get important informations :",1);



    Serial* com = new Serial(port);


    com->start();


    //------------------------------------------------------------------------------

    FenPrincipale w(com);
    w.setWindowTitle("R�cup�rateur des informations re�ues par le biais du Kiwi au melon.");
    w.show();

    //------------------------------------------------------------------------------

    return a.exec();
}

/*

 table (TableView) => Tableau data;
 container(GridLayout) => Tableau de bord
 console (QPlainTextEdit) => Affichage debug;

 */
