#include "sensor.h"

Sensor::Sensor(SensorManager* i_parent,QString i_name, int i_id) : name(i_name), id(i_id)
{
    parent = i_parent;
}

void Sensor::addSensorValue(SensorValue *v) {
    sensorValues.append(v);
}
