#include <QtGui/QApplication>
#include "chronoreaderwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        ChronoReaderWidget w;
        w.show();

    w.laucherCounter(QTime(14,47));

    return a.exec();
}
