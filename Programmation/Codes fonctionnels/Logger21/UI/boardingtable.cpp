#include "boardingtable.h"

BoardingTable::BoardingTable(QGridLayout *container,SensorManager *mgr)
{
    m_container = container;

    init(mgr);
}

BoardingTable::~BoardingTable() {

}

void BoardingTable::init(SensorManager* mgr) {
    QStringList names, values;
    foreach(Sensor* s, mgr->getSensors())
        names << s->getName();

    for(int i=0;i<names.size();i++) {

        QGroupBox* g = new QGroupBox(names[i]);
        QGridLayout* l = new QGridLayout;

        g->setLayout(l);

        capteurs_layouts.append(l);
        m_container->addWidget(g, (int)(i/2) , i%2);

        foreach(SensorValue* v, mgr->getSensor(i)->getValues())
            values << v->getName();

        for(int v = 0; v < mgr->getSensor(i)->getValues().size(); v++) {
            QLabel *l = new QLabel(values[v]);
            capteurs_layouts[i]->addWidget(l,v,0);

            QLCDNumber *lcd = new QLCDNumber(8);
            lcd->display(42);
            valeurs.append(lcd);
            capteurs_layouts[i]->addWidget(lcd,v,1);
        }

        values.clear();
    }
}

void BoardingTable::update(SensorValue* newSV) {
    QGridLayout* layout = capteurs_layouts[newSV->getCapteur()->getId()];
    QLCDNumber *lcd = (QLCDNumber*)layout->itemAtPosition(newSV->getID(),1)->widget();
    lcd->display(newSV->getData()[newSV->getData().size()-1].value);
}
