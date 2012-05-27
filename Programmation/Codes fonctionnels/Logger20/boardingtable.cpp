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
    QStringList values = l.getValueNames();
    for(int i=1;i<=names.size();i++) {

        QGroupBox* g = new QGroupBox(names[i-1]);
        QGridLayout* l = new QGridLayout;

        g->setLayout(l);

        capteurs_layouts.append(l);
        m_container->addWidget(g, (int)((i-1)/2) , (i-1)%2);
    }

    for(int c=0;c<capteurs_layouts.size();c++) {
        for(int v = 0; v < 10; v++) {
            if(values[c*10+v] != "-1") {
                QLabel *l = new QLabel(values[c*10+v]);
                capteurs_layouts[c]->addWidget(l,v,0);

                QLCDNumber *lcd = new QLCDNumber(8);
                lcd->display(42);
                valeurs.append(lcd);
                capteurs_layouts[c]->addWidget(lcd,v,1);

            }
        }
    }
}

void BoardingTable::update(Line* l) {
    QVector<double> values = l->getRawValues();

    for(int i=0;i<valeurs.size();i++) {

        valeurs[i]->display(values[i]);
    }
}
