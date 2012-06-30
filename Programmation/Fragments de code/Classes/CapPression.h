#ifndef CapteurDePression_h
#define CapteurDePression_h

#include <inttypes.h>
#include "Arduino.h"

#include "CapteurAnalog.h"


class CapPression : public CapteurAnalog {
   public:
      CapPression(int a_patte = 1);
     
      bool flush();
      
   private:
      float pression;               //Pas trop de biere SVP

};

#endif