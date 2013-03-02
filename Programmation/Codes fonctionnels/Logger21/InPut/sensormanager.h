#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QVector>
#include "sensor.h"
#include "sensorvalue.h"
#include "FenPrincipale.h"
#include "tablemgr.h"
#include <QHttp>
#include <QUrl>

class FenPrincipale;
class Sensor;

class SensorManager
{
public:
    SensorManager(FenPrincipale *_parent);
    Sensor* getSensor(int id);
    QVector<Sensor*> getSensors() {return sensorList;}
    Data* addData(QString trame, TableMgr *tableManager);
    FenPrincipale* getParent(){return parent;}
protected:
    void getSensorsFromFile();
    QString get_checksum(QString);
private:
    QVector<Sensor*> sensorList;
    FenPrincipale* parent;
    int precIdCapteur;
    int precIdValeur;
};

#endif // SENSORMANAGER_H
