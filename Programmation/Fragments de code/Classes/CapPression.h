#ifndef CapteurDePression_h
#define CapteurDePression_h

#include <inttypes.h>
#include "Arduino.h"


class CapPression {
   public:
      CapPression(int a_patte = 1);
      
      int getValue();
      int getAltitude();
      
   private:
      int patte;

};

#endif