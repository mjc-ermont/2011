#ifndef CAPTEUR_INCLUDED
#define CAPTEUR_INCLUDED

#include <Arduino.h>
#include "vector.h"
#include "out.h"

/*
    Classe capteur :
      Classe mere de toutes les classe capteurs, permet de faire un tableau de capteurs
*/

class Capteur {
public:
	Capteur(const byte &id_capt, const byte &nb_val);
	virtual bool init() = 0;      // Initialisation du capteur
	virtual bool refresh() = 0;   // Recuperation des infos du capteur
        virtual void getTrame();  // Envoi des infos du capteur a toutes les sorties
        virtual void addOut(Out *out);// Ajoute une sortie au capteur
        ~Capteur();

protected:
        Vector<Out*> _out;             // Tableau des sorties du capteur
        char **_val;          // Tableau contenant les valeurs des captoeurs
        const byte _id_capt;
        const byte _nb_val;
        byte _nb_out;
};

#endif
