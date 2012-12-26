#include <Arduino.h>
#include "capteur_analog.h"

class Press : public CapteurAnalog {
public:
	Press(int pin);
	bool init(); // Initialisation du capteur
	bool refresh();  // Recuperation de la valeur de la pression
        void getTrame(); // Envoi de la trame

private:
        String  _press;  // Pression
};
