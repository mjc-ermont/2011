#include "tablemgr.h"

TableMgr::TableMgr(QVector<QTableView*> *tab_historique)
{
      m_tab_historique = tab_historique;
}

void TableMgr::addData(SensorValue *valeur) {
    SensorManager* sensormgr = valeur->getCapteur()->getParent();
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
                   if(i_valeur==0) {
                       QList<QStandardItem*> items;
                       for(int i=0;i<sensormgr->getSensor(i_capteur)->getValues().size();i++) {
                           QStandardItem* curElement  = new QStandardItem;

                           curElement->setText("nul");
                           items << curElement;
                       }
                       ((QStandardItemModel*)m_tab_historique->at(i_capteur)->model())->appendRow(items);

                   }

                   QString dataValue = QString::number(d[i_data]->value);
                   QStandardItemModel* curModel = ((QStandardItemModel*)m_tab_historique->at(i_capteur)->model());
                   QStandardItem* item = curModel->item(i_data,i_valeur);

                   if(item != NULL)
                        item->setText(dataValue);
               }
            }
        }
        bool beat = true;
        while(beat) {
            beat = false;
            for(int i_capteur=0;i_capteur<sensormgr->getSensors().size();i_capteur++) {
                QStandardItemModel* curModel = ((QStandardItemModel*)m_tab_historique->at(i_capteur)->model());
                for(int i=0;i<curModel->rowCount();i++) {
                    bool noProblem = false;

                    for(int v=0;v<sensormgr->getSensor(i_capteur )->getValues().size();v++) {
                        if(curModel->item(i,v)->text() != "nul")
                            noProblem = true;
                    }

                    if(!noProblem) {
                        beat = true;
                        curModel->removeRow(i);
                    }
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
