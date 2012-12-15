#include "pression.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>

Press::Press(){
}

bool Press::init(){
}

bool Press::refresh(){
   int sensorValue;
   sensorValue = analogRead(8);  
   
   float volt = ((float)sensorValue*5)/1023;
   float pr = ((volt-0.2)/(0.045));
   
   _press = String((int)(pr*100));

}

void Press::getTrame(){
    String trame = "#$";
    trame += ID_CAPT_PRESS;
    trame += "$0$";
    for (byte j = 0 ;  j < SIZE_VALUE - _press.length() ; j++) trame += "0";
    trame += _press;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    for (byte k = 0 ; k < NB_REPET ; k++) Serial.print(trame);
    Serial.flush();
}
