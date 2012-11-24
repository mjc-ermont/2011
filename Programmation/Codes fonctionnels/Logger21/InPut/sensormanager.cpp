#include <QtXml/QtXml>
#include "sensormanager.h"

SensorManager::SensorManager() {
    getSensorsFromFile();
}

void SensorManager::getSensorsFromFile() {
    QXmlStreamReader reader;
    QFile cptConfig("conf/cplist.xml");
    reader.setDevice(cptConfig);
    reader.readNext();
    Sensor* curSensor;
    while(!reader.atEnd()) {
        if(reader.name() == "sensor") {
            Sensor *s = new Sensor(reader.attributes().value("name").toString(),reader.attributes().value("id").toString().toInt());
            curSensor = s;
            sensorList.append(s);
        }
        if(reader.name() == "value") {
            SensorValue *sv = new SensorValue(reader.attributes().value("name").toString(),reader.attributes().value("unit").toString(),reader.attributes().value("id").toString().toInt());
            if(curSensor != NULL)
                curSensor->addSensorValue(sv);
        }
        reader.readNext();
    }
}

Sensor* SensorManager::getSensor(int id) {
    for(int i=0;i<sensorList.size();i++) {
        if(sensorList[i]->getId() == id)
            return sensorList[i];
    }
    return NULL;
}
