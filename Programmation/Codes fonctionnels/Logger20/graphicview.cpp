#include "graphicview.h"

GraphicView::GraphicView(Donnees *data, int indexCapteur, int indexValeur, FenPrincipale *parent) :
    QwtPlot(parent), m_capteur(indexCapteur), m_valeur(indexValeur)
{
    courbe = new QwtPlotCurve("Courbe");

    m_data = data;
    m_parent = parent;

    Line l;

    setWindowTitle(l.getCapteursNames()[m_capteur] + " - " + l.getValueNames()[m_capteur * NB_VALEURS_MAX + m_valeur]);


    courbe->attach(this);
    majCurve();

}

void GraphicView::majData(Donnees *data) {
    m_data = data;
    majCurve();
}

void GraphicView::majCurve() {
    calculateCurve();
    courbe->setRawSamples(xValues.data(),yValues.data(),xValues.size());
    replot();
}

void GraphicView::calculateCurve(QTime maxTime) {
    QVector<QPair<QTime, double> > valeurs = m_data->getData(m_capteur,m_valeur);

    int index = valeurs.size();
    xValues.clear();
    yValues.clear();

    for(int i = index - 1; (i >= 0)/* && (QTime(0,0).secsTo(valeurs[i].first) >=  maxTime.secsTo(QTime::currentTime()))*/; i--) {
        xValues.append(QTime(0,0).secsTo(valeurs[i].first));
        yValues.append(valeurs[i].second);
    }
}
