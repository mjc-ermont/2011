#ifndef BOARDINGTABLE_H
#define BOARDINGTABLE_H

#include <QGridLayout>
#include "Line.h"

class BoardingTable
{
public:
    BoardingTable(QGridLayout *container);
    ~BoardingTable();

    void init();

private:
    QGridLayout *m_container;
    QVector<QGroupBox *> capteurs;
};

#endif // BOARDINGTABLE_H
