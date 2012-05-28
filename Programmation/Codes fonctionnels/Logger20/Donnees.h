#ifndef DONNEES_H
#define DONNEES_H

#include <QtGui>
#include <QtSql>
#include "Line.h"
#include "defines.h"

class Donnees : public QObject
{
    Q_OBJECT

    public:
        Donnees();
        ~Donnees();
        void appendLine(Line* a);

        //-----------------------------

       // bool appendInFile();
        void open();

        QStandardItemModel* toTable(int numCapteur);
        QVector<QPair<QTime, double> > getData(int capteur, int valeur);

    signals:
        void msg(QString message);

    private:
        QVector<Line *> data;
        QVector<QStandardItemModel *> tables;

};

#endif // DONNEES_H
