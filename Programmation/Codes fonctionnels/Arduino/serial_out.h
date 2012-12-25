#ifndef SERIALOUT_INCLUDED
#define SERIALOUT_INCLUDED
#include <Arduino.h>
#include "queue.h"
#include "out.h"


class SerialOut : public Out {
public:
	SerialOut();
	virtual bool init();        // Initialisation du port serie
        virtual void writeQueue();  // Ecriture de la sortie sur le port serie
};

#endif // SERIALOUT_INCLUDED
