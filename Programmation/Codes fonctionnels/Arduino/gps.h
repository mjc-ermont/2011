#include <Arduino.h>

typedef struct {
  int age;
  String id_val;
} Value;

typedef struct {
        String id_capt;
        int nb_values;
	Value *values;
} Sensor_out;

class GPS {
public:
	GPS();
	bool init();
	bool refresh();
        Sensor_out GetData();

};
