#include <Arduino.h>
#include "ADXL345.h"

class Hum {
public:
	Hum();
	bool init();
	bool refresh();
        void getTrame();

private:
        String  _hum;
        String  _temp;
};
