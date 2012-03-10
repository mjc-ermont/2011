#ifndef LINE_H
#define LINE_H

#include <QtGui>

class Line : public QObject
{
    Q_OBJECT

    public:
        explicit Line(QObject *parent = 0);
        QList<QStandardItem *> toList() const;

    signals:

    public slots:

    private:
        QDateTime time;

    public:
        double altitude;

        double vith;
        double vitv;

        double tempout;
        double tempin;

        double temphyg;
        double hyg;

        double pressout;
        double pressin;

        double gpsx;
        double gpsy;
        double gpsaltitude;

        double CH4;
        double CO2;

        double GyrX;
        double GyrY;
        double GyrZ;
};

#endif // LINE_H
