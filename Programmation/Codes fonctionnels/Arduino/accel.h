#include <Arduino.h>
#include "ADXL345.h"
#include "vector.h"
#include "out.h"
#include "capteur.h"

class Accel : public Capteur{
public:
	Accel();
	bool init();
	bool refresh();
        void getTrame();

private:
        ADXL345 _accel;
        String  _avg;
};
