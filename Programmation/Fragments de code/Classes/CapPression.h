#ifndef CapteurDePression_h
#define CapteurDePression_h

#include <inttypes.h>
#include "Arduino.h"

#include "Capteur.h"


class CapPression : public Capteur {
   public:
      CapPression(int a_patte = 1);
      
      float getValue();
      float getAltitude();

};

#endif