#include <Arduino.h>
#include "ADXL345.h"
#include "vector.h"
#include "out.h"

class Accel {
public:
	Accel();
	bool init();
	bool refresh();
        void getTrame();
        void addOut(Out &out);

private:
        ADXL345 _accel;
        String  _avg;
        Vector<Out> _out;
};
