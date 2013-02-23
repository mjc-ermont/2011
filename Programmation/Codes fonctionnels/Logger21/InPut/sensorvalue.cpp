#include "sensorvalue.h"


SensorValue::SensorValue(QString i_name, QString i_unit, int i_id, Sensor *i_parent, double i_coef, QString i_param) {
    name = i_name;
    unit = i_unit;
    id = i_id;
    parent = i_parent;
    coef = i_coef;
    param = i_param;
}

Data* SensorValue::addData(double d) {
    Data *newData = new Data;
    newData->time = QTime::currentTime();
    newData->value = d;

    datalist.append(newData);
    qDebug()<<"Param: " << param;
    if(param == "ymap2") { // Updating map
        qDebug() << "I can haz cheeseburger";
        double NDeg=999, NMin=999, WDeg=999,WMin=999;
        NMin = d;
        QVector<SensorValue*> values = parent->getValues();
        for(int i=0;i<values.size();i++) {
            if(values.at(i)->getParam() == "ymap1") {
                NDeg = values.at(i)->getData().last()->value;
            } else if(values.at(i)->getParam() == "xmap1") {
                WDeg = values.at(i)->getData().last()->value;
            } else if(values.at(i)->getParam() == "xmap2") {
                WMin = values.at(i)->getData().last()->value;
            }
        }

        qDebug() << "N" << NDeg << "°" << NMin << "\"" << " W" << WDeg << "°" << WMin << "\"";

        if((NDeg!=999)&&(NMin!=999)&&(WDeg!=999)&&(WMin!=999)) {
            double x = WDeg + WMin/60.0;
            double y = NDeg + NMin/60.0;

            parent->getParent()->getParent()->getMap()->addPoint(x,y);
        }
    }
    return newData;
}
