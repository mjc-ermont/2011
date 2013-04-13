#include "graphicview_.h"

GraphicView::GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent) :
    m_capteur(indexCapteur), m_valeur(indexValeur) {
    m_parent = parent;

    QFile f("html/chart.html");
    f.open(QFile::ReadOnly);
    this->setHtml(f.readAll());
    f.close();
}

void GraphicView::addPoint(QTime t, double v) {
    this->page()->mainFrame()->evaluateJavaScript("addPoint("+QString::number(TimeCalcs::toMs(t))+","+QString::number(v)+")");
}

void GraphicView::majData() {
    addPoint(value->getData()[value->getData().size()-1]->time,value->getData()[value->getData().size()-1]->value);
}

void GraphicView::majData(QTime n_duration) {

}

void GraphicView::majCurve() {

}

void GraphicView::calculateCurve(QTime maxTime) {

}
