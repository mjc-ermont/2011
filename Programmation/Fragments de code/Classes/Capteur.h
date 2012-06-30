#ifndef CAPTEUR_h
#define CAPTEUR_h

#include "arduino.h"

#include "IdCapteurs.h"

class Capteur{
   public:
	  Capteur();
      virtual void init() = 0;
      virtual void refresh() = 0;
      
      virtual bool flush();              //C'est du bluf, augmente la mise ...\\
  
   private:
      String trame;

};

#endif atoi