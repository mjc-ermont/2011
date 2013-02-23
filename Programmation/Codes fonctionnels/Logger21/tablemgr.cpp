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
    }

    while(line[idcapteur].size() <= idvaleur) {
        line[idcapteur].push_back("null");
    }

    line[idcapteur][idvaleur] = QString::number(valeur->getData().last()->value);
  //  line[idcapteur][0] = valeur->getData().last()->time.toString();



    if(lineFull(idcapteur)) {
        update(idcapteur);
        qDebug() << "LINE FULL = UPDATE "<<idcapteur;
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
