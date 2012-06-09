#include "mapsview.h"

MapsView::MapsView(QWidget *parent) : QWebView(parent)
{
    QFile fichier(":/html/maps");
    fichier.open(QFile::ReadOnly);
    QString s= QString(fichier.readAll());
    qDebug() << s;
    this->setHtml(s);

    index = 0;

}

void MapsView::addPoint(int x, int y) {

    QWebFrame* f = this->page()->mainFrame();

    f->evaluateJavaScript("addMarker(" + QString::number(x) + "," + QString::number(y) + "," + QString::number(index) + ")");
    index++;
}
