#ifndef GPS_INCLUDED
#define GPS_INCLUDED

#include <Arduino.h>
#include "capteur.h"

class GPS : public Capteur {
public:
	GPS(const byte &id);
	bool init();
	bool refresh();
        //void getTrame();

private:
};

#endif
