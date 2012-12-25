#include <Arduino.h>

class Press {
public:
	Press();
	bool init(); // Initialisation du capteur
	bool refresh();  // Recuperation de la valeur de la pression
        void getTrame(); // Envoi de la trame

private:
        String  _press;  // Pression
};
