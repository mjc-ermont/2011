#include "graphicview.h"

GraphicView::GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent) :
    QwtPlot(parent), m_capteur(indexCapteur), m_valeur(indexValeur) {
    m_parent = parent;
    value = m_parent->getSensorMgr()->getSensor(indexCapteur)->getValues().at(indexValeur);
    courbe = new QwtPlotCurve("Courbe");
    courbe->setStyle(QwtPlotCurve::Lines);
    courbe->setPen(QPen(QBrush(Qt::black),2));

    setWindowTitle(value->getCapteur()->getName() + " - " + value->getName());

    courbe->attach(this);
    majCurve();
}

void GraphicView::majData() {
    majCurve();
}

void GraphicView::majCurve() {
    calculateCurve();

    QwtSplineCurveFitter* fitter = new QwtSplineCurveFitter;

    fitter->setFitMode(fitter->Auto);
    fitter->setSplineSize(50);

    courbe->setCurveFitter(fitter);

    courbe->setRawSamples(xValues.data(),yValues.data(),xValues.size());
    replot();
}

void GraphicView::calculateCurve(QTime maxTime) {
    foreach(Data d, value->getData()) {
        if(QTime(0,0).secsTo(d.time) >=  maxTime.secsTo(QTime::currentTime())) {
            xValues.append(m_parent->getDepart().secsTo(d.time));
            yValues.append(d.value);
        }
    }
}
