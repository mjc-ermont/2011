#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include "sensorvalue.h"
#include "sensormanager.h"

class SensorValue;
class SensorManager;

class Sensor
{
public:
    Sensor(SensorManager* i_parent,QString i_name, int i_id);
    void addSensorValue(SensorValue* v);
    int getId() { return id;}
    QString getName() { return name;}
    QVector<SensorValue*> getValues() { return sensorValues;}
    SensorManager* getParent(){return parent;}
private:
    QString name;
    int id;
    QVector<SensorValue*> sensorValues;
    SensorManager* parent;
};

#endif // SENSOR_H
