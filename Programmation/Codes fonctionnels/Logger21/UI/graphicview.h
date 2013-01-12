#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H



#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_curve_fitter.h>

//#include <Donnees.h>
#include <FenPrincipale.h>
#include <InPut/sensorvalue.h>
#include <InPut/sensor.h>

class FenPrincipale;

namespace Ui {
class FenPrincipale;
}

class GraphicView : public QwtPlot
{
    Q_OBJECT

    public:
        explicit GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent = 0);
        void majData();

    protected:
        void calculateCurve(QTime maxTime = QTime(0,1));
        void majCurve();


    private:
        int m_capteur;
        int m_valeur;

        FenPrincipale *m_parent;

        QwtPlotCurve* courbe;
        QVector<double> xValues;
        QVector<double> yValues;

        SensorValue *value;
};

#endif // GRAPHICVIEW_H
