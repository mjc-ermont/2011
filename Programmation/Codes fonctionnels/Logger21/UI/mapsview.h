#ifndef MAPSVIEW_H
#define MAPSVIEW_H


#include <QWebView>
#include <QWebFrame>
#include <QFile>
#include <FenPrincipale.h>
#include <defines.h>

class MapsView : public QWebView
{
    Q_OBJECT
public:
    explicit MapsView(QVBoxLayout *parent = 0);

    void addPoint();

    void updateX(double x);
    void updateY(double y);


private:
    QVector<QPair<double,double> > points;
    double mX,mY;
};

#endif // MAPSVIEW_H
