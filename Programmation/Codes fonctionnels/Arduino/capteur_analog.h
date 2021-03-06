#ifndef CAPTEUR_ANALOG_INCLUDED
#define CAPTEUR_ANALOG_INCLUDED

#include <Arduino.h>
#include "vector.h"
#include "out.h"
#include "capteur.h"

/*
    Classe capteur :
      Classe mere de toutes les classe capteurs analogiques
*/

class CapteurAnalog : public Capteur{
public:
	CapteurAnalog(byte id, int pin); // Declaration du capteur avec sa pin
        virtual bool refresh();
        virtual bool init();
protected:
        int _pin; // Patte sur laquelle le capteur est connecté
};

#endif
