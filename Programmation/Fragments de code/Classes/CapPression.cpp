#include "TestTemporaireChimiqueDeClassePourSavoirSiCestCommeCaQuIlFautQueJeFasseIII.h"

CapPression::CapPression(int a_patte){
   patte = a_patte;
}

int CapPression::getValue(){
   float sensorValue = analogRead(1)*5/1023;
   
   return (sensorValue)*25;
}

int CapPression::getAltitude(){
   float sensorValue = analogRead(1)*5/1023;
   
   return -99.01*pow(sensorValue,5) + 1135*pow(sensorValue,4) - 4843.2*pow(sensorValue,3) + 9980.9*pow(sensorValue,2) - 13661*sensorValue + 15781;
}