#include "CapteurAnalog.h"

CapteurAnalog::CapteurAnalog(int a_patte){
   Capteur();
   patte = a_patte;
}

float CapteurAnalog::getValue{
   return value;
}

void refresh(){
    value = analogRead(patte);
}