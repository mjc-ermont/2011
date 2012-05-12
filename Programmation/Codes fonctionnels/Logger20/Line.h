#ifndef LINE_H
#define LINE_H

#include <QtGui>

#define NB_CAPTEURS 6

class Line : public QObject
{
    Q_OBJECT

    public:
        explicit Line(QObject *parent = 0);
        QList<QStandardItem *> toList() const;

        QString addData(QString trame);

        bool checkComplete();
        void clear();

        QStringList getCapteursNames() { return capteurNames ;}
        QStringList getValueNames();

    protected:
        int get_checksum(const char *trame);

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