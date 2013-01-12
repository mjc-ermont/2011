#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include "sensorvalue.h"

class SensorValue;

class Sensor
{
public:
    Sensor(QString i_name, int i_id);
    void addSensorValue(SensorValue* v);
    int getId() { return id;}
    QString getName() { return name;}
    QVector<SensorValue*> getValues() { return sensorValues;}
private:
    QString name;
    int id;
    QVector<SensorValue*> sensorValues;
};

#endif // SENSOR_H
