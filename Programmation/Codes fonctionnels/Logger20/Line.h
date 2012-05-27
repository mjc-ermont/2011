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

        QStringList getCapteursNames() { return capteurNames ;}
        QStringList getValueNames();

        QVector<double> getRawValues();

        void randUpdate();

    protected:
        QString get_checksum(const char *trame);

    signals:
        void complete();
    public slots:

    private:
        QDateTime heure;

        QVector<QPair<QString, double> > content;
        QStringList capteurNames;
        /* Index vecteur = index capteur * 10 + index valeur
         * QString = nom capteur
         * double = valeur capteur
         */
};

#endif // LINE_H
