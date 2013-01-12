#include <QtXml/QtXml>
#include "sensormanager.h"

SensorManager::SensorManager(FenPrincipale* _parent) {
    getSensorsFromFile();
    parent = _parent;
}

void SensorManager::getSensorsFromFile() {
    QXmlStreamReader reader;
    QFile* cptConfig = new QFile("conf/cplist.xml");
    cptConfig->open(QIODevice::ReadOnly);
    reader.setDevice(cptConfig);
    reader.readNext();
    Sensor* curSensor;
    while(!reader.atEnd()) {
        if((reader.name() == "sensor")&&(reader.attributes().value("name").toString() != "")) {
            Sensor *s = new Sensor(reader.attributes().value("name").toString(),reader.attributes().value("id").toString().toInt());
            curSensor = s;
            sensorList.append(s);
            qDebug() << "New sensor:" << s->getName();
        }
        if((reader.name() == "value")&&(reader.attributes().value("name").toString() != "")) {
            SensorValue *sv = new SensorValue(reader.attributes().value("name").toString() ,reader.attributes().value("unit").toString(),reader.attributes().value("id").toString().toInt(),curSensor);
            if(curSensor != NULL)
                curSensor->addSensorValue(sv);

            qDebug() << "  New value:" << sv->getName();
            qDebug() << "  For:" << curSensor->getName();
        }
        reader.readNext();
    }
}

Sensor* SensorManager::getSensor(int id) {

    qDebug() << "id: "<< id << "size: "<< sensorList.size();
    return sensorList[id];
}


QString SensorManager::addData(QString trame) {
    QString erreur = "OK";

    QStringList elements = trame.split("$");
    if(elements.size() < 5)
        return "Ya un bug lol.";

    QString firstPart = elements[0] + "$" + elements[1] + "$" + elements[2] + "$" + elements[3] + "$";
    QString checkSum = get_checksum(firstPart);
    qDebug() << "CS: "<< QString(checkSum).toInt(NULL, 10) << " | "  << elements[4].toInt(NULL, 16) ;
    if(QString(checkSum).toInt(NULL, 10) == elements[4].toInt(NULL, 16) ) {
        int numCapteur = elements[1].toInt();
        double valeur = elements[3].toDouble();
        int numValeur = elements[2].toInt();

        if(numCapteur == 2) // LE PUTAIN DE CAPTEUR D'ARTHUR QU'IL FAUT DIVISER PAR 100
            valeur = valeur / 100;

        sensorList[numCapteur]->getValues()[numValeur]->addData(valeur);
        parent->getBT()->update(sensorList[numCapteur]->getValues()[numValeur]);
    } else {
        erreur = "Mauvais checksum.";
    }

    return erreur;
}

QString SensorManager::get_checksum(QString trame) {

    char XOR = 0;
    for (int i = 0; i < trame.length() ; i++)
    {
       XOR = XOR ^ trame.toStdString()[i];
    }

    qDebug() << XOR;

    return QString::number(XOR);
}
