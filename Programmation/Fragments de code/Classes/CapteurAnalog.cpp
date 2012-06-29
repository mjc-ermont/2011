#include "CapteurAnalog.h"

CapteurAnalog::CapteurAnalog(int a_patte){
   Capteur();
   patte = a_patte;
}

void refresh(){
    value = analogRead(patte);
}

float CapteurAnalog::flush(){
   return value;
}