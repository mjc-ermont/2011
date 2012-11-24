#include <QtGui/QApplication>
#include "chronoedit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChronoEdit w;
    w.show();
    
    return a.exec();
}
