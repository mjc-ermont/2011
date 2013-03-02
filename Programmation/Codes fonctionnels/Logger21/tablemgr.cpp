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

  //  bool updateLine=false;

   // if(bef_line[idcapteur][idvaleur+1] != QString::number(valeur->getData().last()->value)) {
        line[idcapteur][idvaleur+1] = QString::number(valeur->getData().last()->value);
        line[idcapteur][0] = valeur->getData().last()->time.toString();
      //  bef_line[idcapteur][idvaleur+1]=QString::number(valeur->getData().last()->value);
     //   updateLine=true;
   // }


    if(lineFull(idcapteur)) {
        update(idcapteur);
        qDebug() << "LINE FULL = UPDATE"<<idcapteur;
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
