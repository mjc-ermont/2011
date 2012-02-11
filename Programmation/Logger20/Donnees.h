#ifndef DONNEES_H
#define DONNEES_H

#include <QStandardItemModel>
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
};

#endif // DONNEES_H
