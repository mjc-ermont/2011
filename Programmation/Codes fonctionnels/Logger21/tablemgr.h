#ifndef TABLEMGR_H
#define TABLEMGR_H

#include "InPut/sensorvalue.h"
#include "defines.h"
#include <QtGui>

class TableMgr
{
public:
    TableMgr(QVector<QTableView*>* tab_historique);
    void addData(SensorValue *valeur);
protected:
    void update(int capteur);
    bool lineFull(int capteur);
private:
    QVector<QTableView*> *m_tab_historique;
    QVector<QVector<QString> > line;
    QVector<QVector<QString> > bef_line;
};

#endif // TABLEMGR_H
