#include <Arduino.h>
#include "capteur_analog.h"

class Temp : public CapteurAnalog{
public:
	Temp(int pin);
	bool init(); // Initialisation du capteur
	bool refresh();  // Recuperation de la temperature
        void getTrame(); // Envoi de la trame

private:
        String  _temp;  // Temperature
};
