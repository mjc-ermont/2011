#include "CapPression.h"

CapPression::CapPression(int a_patte){
   Capteur();
}

void CapPression::refresh(){
   float sensorValue = Capteur::getvalue()*5/1023;
   String pression = ftoa(sensorValue*25);
   
   trame  = "#";
   trame += "$";
   trame += ID_CAPPRESSION;
   trame +=  ID_CAPPRESSION_PRESSION;
   trame += "$";
   trame += pression;
      for(byte i = 0 ; i < SIZE_VALUE - pression.lenght() ; i ++)
   trame += "0";
   trame += "$";
   trame += get_checksum(trame);
   trame += "$";
   trame += "@";
}