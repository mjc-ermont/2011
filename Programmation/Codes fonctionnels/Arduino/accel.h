#ifndef ACCEL_INCLUDED
#define ACCEL_INCLUDED

#include <Arduino.h>
#include "ADXL345.h"
#include "vector.h"
#include "out.h"
#include "capteur.h"

class Accel : public Capteur{
public:
	Accel();
	bool init(); // methode de recuperation des donnees de l'accelerometre
	bool refresh(); // methode de recuperation des donnees de l'accelerometre
        void getTrame(); // methode d'envoi de la trame

private:
        ADXL345 _accel; // Objet pour gérer accelerometre
        String  _avg; // Norme du vecteur acceleration
};
#endif
