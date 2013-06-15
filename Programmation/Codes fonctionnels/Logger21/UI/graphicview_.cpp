#include "graphicview_.h"

GraphicView::GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent) :
    m_capteur(indexCapteur), m_valeur(indexValeur) {
    m_parent = parent;

    value = m_parent->getSensorMgr()->getSensor(indexCapteur)->getValues()[indexValeur];

    this->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    this->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    this->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    this->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    this->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    this->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    this->load(QUrl("qrc:///html/chart.html"));

    //this->page()->mainFrame()->evaluateJavaScript("setValue("+m_parent->getSensorMgr()->getSensor(indexCapteur)->getValues()[indexValeur]->getName()+";"+m_parent->getSensorMgr()->getSensor(indexCapteur)->getValues()[indexValeur]->getUnit()+")");
    this->show();


    QVector<Data*> d = value->getData();
    for(int i=0;i<d.size();i++) {
        addPoint(d.at(i)->time, d.at(i)->value);
    }

    QTimer t;
    t.start(3000);

    connect(&t, SIGNAL(timeout()), this, SLOT(updateTitle()));
}

void GraphicView::addPoint(QTime t, double v) {
    this->page()->mainFrame()->evaluateJavaScript("addPoint("+QString::number(TimeCalcs::toMs(t))+","+QString::number(v)+")");
}

void GraphicView::majData() {
    if(value->getData().size()-1 < 0)
        return;

    addPoint(value->getData()[value->getData().size()-1]->time,value->getData()[value->getData().size()-1]->value);
}

void GraphicView::updateTitle() {

    this->page()->mainFrame()->evaluateJavaScript("setTitle("+m_parent->getSensorMgr()->getSensor(m_capteur )->getName()+")");

}

void GraphicView::majData(QTime n_duration) {}

void GraphicView::majCurve() {}

void GraphicView::calculateCurve(QTime maxTime) {}

