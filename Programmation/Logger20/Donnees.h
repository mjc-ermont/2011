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
        void appendLine(Line* a);

        bool appendInFile(Line* a);
        void open();

    signals:
        void msg(QString message);

    private:
        QSqlDatabase db;
};

#endif // DONNEES_H
