#include <Arduino.h>

class Temp {
public:
	Temp();
	bool init(); // Initialisation du capteur
	bool refresh();  // Recuperation de la temperature
        void getTrame(); // Envoi de la trame

private:
        String  _temp;  // Temperature
};
