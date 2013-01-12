#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QVector>
#include "sensor.h"
#include "sensorvalue.h"
#include "FenPrincipale.h"

class FenPrincipale;

class SensorManager
{
public:
    SensorManager(FenPrincipale *_parent);
    Sensor* getSensor(int id);
    QVector<Sensor*> getSensors() {return sensorList;}
    QString addData(QString trame);
protected:
    void getSensorsFromFile();
    QString get_checksum(QString);
private:
    QVector<Sensor*> sensorList;
    FenPrincipale* parent;
};

#endif // SENSORMANAGER_H
