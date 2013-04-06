#ifndef TABLEMGR_H
#define TABLEMGR_H

#include "InPut/sensorvalue.h"
#include "defines.h"
#include <QtGui>
#include "../ChronoReaderWidget/TimeCalcs/timecalcs.h"

class TableMgr
{
public:
    TableMgr(QVector<QTableView*>* tab_historique);
    void addData(SensorValue *valeur);
    void addData(SensorValue *valeur,int index,QTime start, QTime end);
    void actualisay(QTime start,QTime end,SensorManager* sensormgr);
protected:
    void update(int capteur);
    bool lineFull(int capteur);
private:
    QVector<QTableView*> *m_tab_historique;
    QVector<QVector<QString> > line;
    QVector<QVector<QString> > bef_line;
};

#endif // TABLEMGR_H
