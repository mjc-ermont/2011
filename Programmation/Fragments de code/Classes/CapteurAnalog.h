#ifndef CapteurAnalog_h
#define CapteurAnalog_h

#include <inttypes.h>
#include "Arduino.h"

#include "Capteur.h"


class CapteurAnalog : public Capteur{
   public:
      Capteur(int a_patte = 1);
      
      float getValue();
      void refresh();
      
   private:
      int patte;

};

#endif