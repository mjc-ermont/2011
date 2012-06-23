#include <Arduino.h>

typedef struct {
  //int age;
  char *id_val;
  String *val;
} Value;

typedef struct {
        char *id_capt;
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
