#ifndef CAPTEURANALOG_h
#define CAPTEURANALOG_h

#include <inttypes.h>
#include "Arduino.h"

#include "Capteur.h"


class CapteurAnalog : public Capteur{
   public:
      CapteurAnalog(int a_patte = 1);
      
      void init();
      
   protected:
     int getPatte();
      
   private:
      int patte;

};

#endif
