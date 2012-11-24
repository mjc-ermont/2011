#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QVector>
#include "sensor.h"
#include "sensorvalue.h"


class SensorManager
{
public:
    SensorManager();
    Sensor* getSensor(int id);

protected:
    void getSensorsFromFile();
private:
    QVector<Sensor*> sensorList;
};

#endif // SENSORMANAGER_H
