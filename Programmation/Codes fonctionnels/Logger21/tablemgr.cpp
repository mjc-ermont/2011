#include "tablemgr.h"

TableMgr::TableMgr(QVector<QTableView*> *tab_historique)
{
      m_tab_historique = tab_historique;
}

void TableMgr::addData(SensorValue *valeur) {
    int idcapteur = valeur->getCapteur()->getId();
    int idvaleur = valeur->getID();

    while(line.size() <= idcapteur) {
        QVector<QString> v;
        v.push_back("null");
        line.push_back(v);
        bef_line.push_back(v);
    }

    while(line[idcapteur].size() <= idvaleur+1) {
        line[idcapteur].push_back("null");
        bef_line[idcapteur].push_back("null");
    }

    line[idcapteur][idvaleur+1] = QString::number(valeur->getData().last()->value);
    line[idcapteur][0] = valeur->getData().last()->time.toString();



    if(lineFull(idcapteur)) {
        update(idcapteur);
        qDebug() << "LINE FULL = UPDATE"<<idcapteur;
    }
}

void TableMgr::actualisay(QTime start,QTime end,SensorManager* sensormgr) {
    // C'est parti, mon kiki.
    for(int i_capteur=0;i_capteur<sensormgr->getSensors().size();i_capteur++) {
        for(int i_valeur=0;i_valeur<sensormgr->getSensor(i_capteur)->getValues().size();i_valeur++) {
            QVector<Data*> d = sensormgr->getSensor(i_capteur)->getValues()[i_valeur]->getData();
            for(int i_data=0;i_data<d.size();i_data++) {
               if((TimeCalcs::toMs(d[i_data]->time) > TimeCalcs::toMs(start))&&(TimeCalcs::toMs(d[i_data]->time) < TimeCalcs::toMs(end))) {
                   if(i_valeur=0) {
                       QList<QStandardItem*> items;
                       for(int i=0;i<sensormgr->getSensor(i_capteur)->getValues().size();i++) {
                           QStandardItem* curElement  = new QStandardItem;

                           curElement->setText("nul");
                           items << curElement;
                       }
                       ((QStandardItemModel*)m_tab_historique->at(i_capteur)->model())->appendRow(items);

                   }
                   ((QStandardItemModel*)m_tab_historique->at(i_capteur)->model())->item(i_data,i_valeur)->setText(QString::number(d[i_data]->value));
               }
            }
        }
    }
}

bool TableMgr::lineFull(int capteur) {
    bool okay=true;
    foreach(QString value, line[capteur]) {
        if(value == "")
            okay = false;
    }
    return okay;
}

void TableMgr::update(int capteur) {
    QList<QStandardItem*> items;
    foreach(QString value, line[capteur]) {
        QStandardItem* element  = new QStandardItem;
        element->setText(value);
        items << element;
    }
    ((QStandardItemModel*)m_tab_historique->at(capteur)->model())->appendRow(items);
}
