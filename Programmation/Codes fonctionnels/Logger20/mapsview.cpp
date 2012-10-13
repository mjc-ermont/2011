#include "mapsview.h"

MapsView::MapsView(QVBoxLayout *parent) : QWebView()
{
    parent->addWidget(this);

    QFile fichier(":/html/maps");
    fichier.open(QFile::ReadOnly);
    QString s= QString(fichier.readAll());
    qDebug() << s;
    this->setHtml(s);
}

void MapsView::addPoint(double x, double y) {

    qDebug() << "Map";

    QWebFrame* f = this->page()->mainFrame();
    f->evaluateJavaScript("newPos(" + QString::number(x) + "," + QString::number(y) + ")");

    qDebug() << "FMap";
}
