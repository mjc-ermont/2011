#include "CapPression.h"

CapPression::CapPression(int a_patte){
   Capteur();
}

float CapPression::getValue(){
   float sensorValue = Capteur::getvalue()*5/1023;
   
   return (sensorValue)*25;
}

float CapPression::getAltitude(){
   float sensorValue = Capteur::getvalue()*5/1023;
   
   return -99.01*pow(sensorValue,5) + 1135*pow(sensorValue,4) - 4843.2*pow(sensorValue,3) + 9980.9*pow(sensorValue,2) - 13661*sensorValue + 15781;
}