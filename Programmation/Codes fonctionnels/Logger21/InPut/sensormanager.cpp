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
            Sensor *s = new Sensor(this,reader.attributes().value("name").toString(),reader.attributes().value("id").toString().toInt());
            curSensor = s;
            sensorList.append(s);
            qDebug() << "New sensor:" << s->getName();
        }
        if((reader.name() == "value")&&(reader.attributes().value("name").toString() != "")) {
            int coef=1;
            QString params = reader.attributes().value("param").toString();
            SensorValue *sv = new SensorValue(reader.attributes().value("name").toString() ,reader.attributes().value("unit").toString(),reader.attributes().value("id").toString().toInt(),curSensor,coef,params);
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


Data* SensorManager::addData(QString trame,TableMgr* tableManager) {
    QStringList elements = trame.split("$");
    if(elements.size() < 5)
        return NULL;

    QString firstPart = elements[0] + "$" + elements[1] + "$" + elements[2] + "$" + elements[3] + "$";
    QString checkSum = get_checksum(firstPart);

    qDebug() << "Trame:" << trame;
    qDebug() << "CS: "<< QString(checkSum).toInt(NULL, 10) << " | "  << elements[4].toInt(NULL, 16) ;

    bool checkLeSum = true;
    Data *d=NULL;

    if((QString(checkSum).toInt(NULL, 10) == elements[4].toInt(NULL, 16))||(!checkLeSum)) {
        int numCapteur = elements[1].toInt();
        double valeur = elements[3].toDouble();
        int numValeur = elements[2].toInt();

        valeur = valeur * sensorList[numCapteur]->getValues()[numValeur]->getCoef();

        d = sensorList[numCapteur]->getValues()[numValeur]->addData(valeur);
        parent->getBT()->update(sensorList[numCapteur]->getValues()[numValeur]);
        tableManager->addData(sensorList[numCapteur]->getValues()[numValeur]);


        // ICI

      /*  QHttp *requette = new QHttp;
        QUrl url("82.237.11.61");
        requette->setHost(url.host(),QHttp::ConnectionModeHttp,80);
        // Ici nous créons l'entête pour notre requête
        QHttpRequestHeader reqHeader("GET", "/Cookie-WebUI-Server/bin/add.php?t=token&nc="+QString::number(numCapteur)+"&nv="+QString::number(numValeur)+"&v="+QString::number(valeur));
        reqHeader.setValue("Host", "home.konfiot.net");
        requette->request(reqHeader);
        qDebug() << "requette";*/
        QHttp *serveur_search = new QHttp("home.konfiot.net");
        serveur_search->setHost("home.konfiot.net");

        serveur_search->get("/Cookie-WebUI-Server/bin/add.php?t=token&nc="+QString::number(numCapteur)+"&nv="+QString::number(numValeur)+"&v="+QString::number(valeur));


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
