#include "CapteurAnalog.h"

CapteurAnalog::CapteurAnalog(int a_patte){
   Capteur();
   patte = a_patte;
}

void CapteurAnalog::refresh(){
    value = analogRead(patte);
}

int CapteurAnalog::getPatte(){
    return patte;
}
