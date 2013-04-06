#include <QtXml/QtXml>
#include "sensormanager.h"

SensorManager::SensorManager(FenPrincipale* _parent) {
    getSensorsFromFile();
    parent = _parent;
    precIdCapteur=0;
    precIdValeur=0;
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
            Sensor *s = new Sensor(this,reader.attributes().value("name").toString(),reader.attributes().value("id").toString().toInt());
            curSensor = s;
            sensorList.append(s);
            qDebug() << "New sensor:" << s->getName();
        }
        if((reader.name() == "value")&&(reader.attributes().value("name").toString() != "")) {
            int coef=1;
            QString params = reader.attributes().value("param").toString();
            SensorValue *sv = new SensorValue(reader.attributes().value("name").toString() ,reader.attributes().value("unit").toString(),reader.attributes().value("id").toString().toInt(),curSensor,coef,params);

            if(reader.attributes().value("coef").toString().toFloat() != 0)
                sv->setCoef(reader.attributes().value("coef").toString().toDouble());

            if(curSensor != NULL)
                curSensor->addSensorValue(sv);


            qDebug() << "  New value:" << sv->getName();
            qDebug() << "  For:" << curSensor->getName();
        }
        reader.readNext();
    }
}

Sensor* SensorManager::getSensor(int id) {
    return sensorList[id];
}


Data* SensorManager::addData(QString trame) {
    QStringList elements = trame.split("$");
    if(elements.size() < 6) {
         qDebug() << "Trame incomplete";
        return NULL;
    }

    QString firstPart = elements[0] + "$" + elements[1] + "$" + elements[2] + "$" + elements[3] + "$";
    QString checkSum = get_checksum(firstPart);

    qDebug() << "Trame:" << trame;
    qDebug() << "CS: "<< QString(checkSum).toInt(NULL, 10) << " | "  << elements[4].toInt(NULL, 16) ;

    bool checkLeSum = true;
    Data *d=NULL;
    int numCapteur = elements[1].toInt();
    double valeur = elements[3].toDouble();
    int numValeur = elements[2].toInt();

    if(((QString(checkSum).toInt(NULL, 10) == elements[4].toInt(NULL, 16))||(!checkLeSum))&&((numCapteur!=precIdCapteur)||(precIdValeur!=numValeur))){
        if(numCapteur < sensorList.size()) {
            if(numValeur < sensorList[numCapteur]->getValues().size()) {
                precIdCapteur=numCapteur;
                precIdValeur=numValeur;

                valeur = valeur * sensorList[numCapteur]->getValues()[numValeur]->getCoef();

                d = sensorList[numCapteur]->getValues()[numValeur]->addData(valeur);
                parent->getBT()->update(sensorList[numCapteur]->getValues()[numValeur]);

                QString url = parent->dataServerLineEdit->text();
                QStringList split = url.split("||");
                if(split.size() == 2) {
                    QHttp *serveur_search = new QHttp(split[0]);
                    serveur_search->setHost(split[0]);

                    serveur_search->get(split[1]+"?t=token&nc="+QString::number(numCapteur)+"&nv="+QString::number(numValeur)+"&v="+QString::number(valeur));
                } else {
                    QHttp *serveur_search = new QHttp("home.konfiot.net");
                    serveur_search->setHost("home.konfiot.net");

                    serveur_search->get("/Cookie-WebUI-Server/bin/add.php?t=token&nc="+QString::number(numCapteur)+"&nv="+QString::number(numValeur)+"&v="+QString::number(valeur));
                }
            }
        }
    }
    return d;
}

QString SensorManager::get_checksum(QString trame) {

    char XOR = 0;
    for (int i = 0; i < trame.length() ; i++) {
       XOR = XOR ^ trame.toStdString()[i];
    }

    return QString::number(XOR);
}
