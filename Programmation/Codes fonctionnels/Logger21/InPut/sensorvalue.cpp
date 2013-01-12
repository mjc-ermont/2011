#include "sensorvalue.h"


SensorValue::SensorValue(QString i_name, QString i_unit, int i_id, Sensor *i_parent, double i_coef, QString i_param) {
    name = i_name;
    unit = i_unit;
    id = i_id;
    parent = i_parent;
    coef = i_coef;
    param = i_param;
}

void SensorValue::addData(double d) {
    Data newData;
    newData.time = QTime::currentTime();
    newData.value = d;

    datalist.append(newData);
}
