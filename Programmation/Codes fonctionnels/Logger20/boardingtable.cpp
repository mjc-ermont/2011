#include "boardingtable.h"

BoardingTable::BoardingTable(QGridLayout *container)
{
    m_container = container;

    init();
}

BoardingTable::~BoardingTable() {

}

void BoardingTable::init() {
    Line l;

    QStringList names = l.getCapteursNames();
    for(int i=1;i<=names.size();i++) {
        QGroupBox* g = new QGroupBox(names[i]);
        capteurs.append(g);

        m_container->addWidget(g,(i-(i%2))/2,i%2);
    }
}
/*
1%2 => 1
2%2 => 0
3%2 => 1

   */
