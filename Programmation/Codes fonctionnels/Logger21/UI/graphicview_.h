#ifndef GRAPHIVIEW__H
#define GRAPHIVIEW__H

#include <QtWebKit>
//#include <Donnees.h>
#include <FenPrincipale.h>
#include <InPut/sensorvalue.h>
#include <InPut/sensor.h>

class FenPrincipale;

namespace Ui {
class FenPrincipale;
}

class GraphicView : public QWebView
{
    Q_OBJECT

    public:
        explicit GraphicView(int indexCapteur, int indexValeur, FenPrincipale *parent = 0);
        void addPoint(QTime t, double v);


        void majData(QTime n_duration);
        void majData();

    public slots:
        void updateTitle();
    protected:
        void calculateCurve(QTime maxTime = QTime(0,1));
        void majCurve();


    private:
        int m_capteur;
        int m_valeur;

        FenPrincipale *m_parent;


        SensorValue *value;
        QTime duration;
};
#endif // GRAPHIVIEW__H
