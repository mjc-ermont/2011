#include "graphicview.h"

GraphicView::GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent) :
    QwtPlot(parent), m_capteur(indexCapteur), m_valeur(indexValeur) {
    m_parent = parent;
    value = m_parent->getSensorMgr()->getSensor(indexCapteur)->getValues().at(indexValeur);
    courbe = new QwtPlotCurve("Courbe");
    courbe->setStyle(QwtPlotCurve::Lines);
    courbe->setPen(QPen(QBrush(Qt::black),2));

    setWindowTitle(value->getCapteur()->getName() + " - " + value->getName());

    duration = QTime(0,5,0);
    courbe->attach(this);
    majCurve();
}

void GraphicView::majData() {
    majCurve();
}

void GraphicView::majData(QTime n_duration) {
    duration=n_duration;
    majCurve();
}

void GraphicView::majCurve() {
    calculateCurve(duration);

    QwtSplineCurveFitter* fitter = new QwtSplineCurveFitter;

    fitter->setFitMode(fitter->Auto);
    fitter->setSplineSize(50);

    courbe->setCurveFitter(fitter);

    courbe->setRawSamples(xValues.data(),yValues.data(),xValues.size());
    replot();
}

void GraphicView::calculateCurve(QTime maxTime) {
    yValues.clear();
    xValues.clear();
    foreach(Data *d, value->getData()) {
        if(QTime(0,0).secsTo(d->time) >=  maxTime.secsTo(QTime::currentTime())) {
            xValues.append(m_parent->getDepart().secsTo(d->time));
            yValues.append(d->value);
        }
    }
}
