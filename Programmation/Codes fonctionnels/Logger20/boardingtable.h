#ifndef BOARDINGTABLE_H
#define BOARDINGTABLE_H

#include <QGridLayout>
#include "Line.h"
#include "defines.h"

class BoardingTable
{
public:
    BoardingTable(QGridLayout *container);
    ~BoardingTable();

    void init();

private:
    QGridLayout *m_container;
    QVector<QGridLayout *> capteurs_layouts;
    QVector<QLCDNumber *> valeurs;
};

#endif // BOARDINGTABLE_H
