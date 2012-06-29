#include "CapPression.h"

CapPression::CapPression(int a_patte){
   Capteur();
}

float CapPression::refresh(){
   float sensorValue = Capteur::getvalue()*5/1023;
   
   pression = sensorValue*25;
}