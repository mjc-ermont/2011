#include <Arduino.h>

typedef struct {
        String name;
	String value;
	int age;
} Sensor_out;

class GPS {
public:
	GPS();
	bool init();
	bool refresh();
        Sensor_out* GetData();

};
