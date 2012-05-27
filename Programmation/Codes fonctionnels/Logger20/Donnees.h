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

        bool appendInFile();
        bool appendInDB(Line* a);
        void open();

        //-----------------------------

        void connect();

        //-----------------------------

        int nbCapteurs() const;
        QStringList listCapteurs() const;
        QVariant capteurInfo(QString capteur, QString type = "display");

        //-----------------------------

        QStandardItemModel *toFen();

    signals:
        void msg(QString message);

    private:
        QSqlDatabase db;
        QStandardItemModel *fenetre;
        QSettings capteurs;

        //-----------------------------

        int colonnes() const;
        int lignes() const;
};

#endif // DONNEES_H
