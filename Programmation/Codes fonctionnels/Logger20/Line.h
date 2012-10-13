#ifndef LINE_H
#define LINE_H

#include <QtGui>
#include "defines.h"

class Line : public QObject
{
    Q_OBJECT

    public:
        explicit Line(QObject *parent = 0);
        QList<QStandardItem *> toList(int numCapteur) const;

        QString addData(QString trame);

        bool checkComplete();
        void clear();

        double getValue(int c, int v);

        QStringList getCapteursNames() { return capteurNames ;}
        QStringList getValueNames();

        QVector<double> getRawValues(); // Retourne les valeurs à la suite sans espacement
        QVector<QPair<QTime,double> > getValuesWithTime(); // Retourne les valeurs, avec l'heure, et l'espacement quand on a une valeur vide.

        void randUpdate(Line* defL);

    protected:
        QString get_checksum(const char *trame);

    signals:
        void complete();
    public slots:

    private:
        QVector<QPair<QString, double> > content;
        QVector<QTime> h_reception;
        QStringList capteurNames;
        /* Index vecteur = index capteur * 10 + index valeur
         * QString = nom capteur
         * double = valeur capteur
         */
};

#endif // LINE_H
