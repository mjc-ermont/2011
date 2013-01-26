#ifndef OUT_INCLUDED
#define OUT_INCLUDED

#include <Arduino.h>
#include "queue.h"



class Out {
public:
	Out();
	virtual bool init() = 0;        // Initialisation de la sortie
        void addTrame(char *trame);    // Ajout de la trame a la file
        virtual void writeQueue() = 0;  // Ecriture de la file sur la sortie
protected:
        QueueList<char*> queue;       // File d'attente
};

#endif
