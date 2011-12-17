#ifndef DONNEES_H
#define DONNEES_H

#include <QtGui>

class Donnees : public QStandardItemModel
{
    Q_OBJECT

    public:
        explicit Donnees(QObject *parent = 0);
        void append(double altitude, double tempout, double tempin, double temphyg, double pressout, double pressin, int gpsx, int gpsy, double CO2, double CH4, double gyrx, double gyry, double gyrz);

        void open();

    signals:
        void msg(QString msg);

    public slots:

    private:
        void saveAppend();

};

#endif // DONNEES_H
