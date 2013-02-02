#include <QtGui>
#include <QInputDialog>
#include <QDebug>
#include <ctime>

#include "defines.h"
#include "FenPrincipale.h"
#include "InPut/serial.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);

    //------------------------------------------------------------------------------
    AskDialog* d = new AskDialog();
    d->show();
    //------------------------------------------------------------------------------

    return a.exec();
}

/*

 table (TableView) => Tableau data;
 container(GridLayout) => Tableau de bord
 console (QPlainTextEdit) => Affichage debug;

 */
