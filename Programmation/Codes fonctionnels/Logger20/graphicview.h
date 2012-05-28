#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H



#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>

#include <Donnees.h>
#include <FenPrincipale.h>

class FenPrincipale;

namespace Ui {
class FenPrincipale;
}

class GraphicView : public QwtPlot
{
    Q_OBJECT

    public:
        explicit GraphicView(Donnees *data, int indexCapteur, int indexValeur, FenPrincipale *parent = 0);
        void majData(Donnees *data);

    protected:
        void calculateCurve(QTime maxTime = QTime(0,1));
        void majCurve();


    private:
        int m_capteur;
        int m_valeur;
        Donnees *m_data;
        FenPrincipale *m_parent;

        QwtPlotCurve* courbe;
        QVector<double> xValues;
        QVector<double> yValues;
    
};

#endif // GRAPHICVIEW_H
