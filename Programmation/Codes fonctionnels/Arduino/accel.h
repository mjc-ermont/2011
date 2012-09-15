#include <Arduino.h>
#include "ADXL345.h"

class Accel {
public:
	Accel();
	bool init();
	bool refresh();
        void getTrame();

private:
        ADXL345 _accel;
        String  _avg;
};
