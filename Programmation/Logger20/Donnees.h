#ifndef DONNEES_H
#define DONNEES_H

#include <QtGui>
#include <QtSql>
#include <Line.h>

class Donnees : public QStandardItemModel
{
    Q_OBJECT

    public:
        Donnees();
        ~Donnees();
        void appendLine(Line* a);

        bool appendInFile();
        void open();

        void connect();

    signals:
        void msg(QString message);

    private:
        QSqlDatabase db;
};

#endif // DONNEES_H
