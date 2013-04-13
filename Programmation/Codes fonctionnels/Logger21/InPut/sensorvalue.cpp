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
    if(param == "xmap") {
        parent->getParent()->getParent()->getMap()->updateX(d);
    } else if(param == "ymap") {
        parent->getParent()->getParent()->getMap()->updateY(d);
    }
    return newData;
}
