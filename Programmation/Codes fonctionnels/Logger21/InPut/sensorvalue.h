#ifndef VALUE_H
#define VALUE_H

#include <QString>
#include <QVector>
#include <defines.h>

#include "sensor.h"
class Sensor;
class SensorValue
{
public:
    SensorValue(QString i_name, QString i_unit, int i_id,Sensor* i_parent);
    void addData(double d);
    QString getName() { return name;}
    QVector<Data> getData() {return datalist;}
    int getID() {return id;}
    Sensor* getCapteur() {return parent;}

private:
    QString name;
    QString unit;
    int id;
    QVector<Data> datalist;
    Sensor* parent;
};

#endif // VALUE_H
