#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include <sensorvalue.h>

class Sensor
{
public:
    Sensor(QString i_name, int i_id);
    void addSensorValue(SensorValue* v);
    int getId() { return id;}
private:
    QString name;
    int id;
    QVector<SensorValue*> sensorValues;
};

#endif // SENSOR_H
