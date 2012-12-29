#ifndef HUMIDITY_INCLUDED
#define HUMIDITY_INCLUDED

#include <Arduino.h>
#include "capteur.h"

class Hum : public Capteur {
public:
	Hum(const byte &id);
	bool init();
	bool refresh();
        //void getTrame();
};

#endif
