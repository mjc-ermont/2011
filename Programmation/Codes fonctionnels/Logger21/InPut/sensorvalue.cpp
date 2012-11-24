#include "sensorvalue.h"


SensorValue::SensorValue(QString i_name, QString i_unit, QString i_id) {
    name = i_name;
    unit = i_name;
    id = i_id;
}

void SensorValue::addData(double d) {
    Data newData;
    newData.time = QTime::currentTime();
    newData.value = d;

    datalist.append(newData);
}
