#include <Arduino.h>
#include "vector.h"
#include "out.h"

/*
    Classe capteur :
      Classe mere de toutes les classe capteurs, permet de faire un tableau de capteurs
*/

class Capteur {
public:
	Capteur();
	virtual bool init() = 0;      // Initialisation du capteur
	virtual bool refresh() = 0;   // Recuperation des infos du capteur
        virtual void getTrame() = 0;  // Envoi des infos du capteur a toutes les sorties
        virtual void addOut(Out &out);// Ajoute une sortie au capteur

protected:
        Vector<Out> _out;             // Tableau des sorties du capteur
};
