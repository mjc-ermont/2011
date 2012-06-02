#include <Arduino.h>

String get_gps_2();
String get_gps_1();

typedef struct {
	String value;
	int age;
} Sensor_out;

class GPS {
public:
	GPS();
	bool init();
	bool refresh();
	Sensor_out get_alt();
	Sensor_out get_vit();
	Sensor_out get_lat_ang();
	Sensor_out get_lat_min();
	Sensor_out get_long_ang();
	Sensor_out get_long_min();
	Sensor_out get_time();

};
