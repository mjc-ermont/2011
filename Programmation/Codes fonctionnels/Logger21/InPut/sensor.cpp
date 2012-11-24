#include "sensor.h"

Sensor::Sensor(String i_name, int i_id) : name(i_name), id(i_id)
{
}

void Sensor::addSensorValue(SensorValue *v) {
    sensorValues.append(v);
}
