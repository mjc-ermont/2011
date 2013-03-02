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
    SensorValue(QString i_name, QString i_unit, int i_id,Sensor* i_parent, double i_coef=1, QString i_param="");
    Data* addData(double d);
    QString getName() { return name;}
    QVector<Data*> getData() {return datalist;}
    int getID() {return id;}
    Sensor* getCapteur() {return parent;}
    double getCoef() { return coef;}
    void setCoef(double p_coef) { coef=p_coef;}
    QString getParam() { return param;}

    QString getUnit() { return unit;}

private:
    QString name;
    QString unit;
    int id;
    double coef;
    QString param;
    QVector<Data*> datalist;
    Sensor* parent;
};

#endif // VALUE_H
