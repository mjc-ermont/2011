#include "pression.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>

Press::Press(byte id, int pin) : CapteurAnalog::CapteurAnalog(id, pin){
}

bool Press::init(){ // Initialisation du capteur
  _val.push_back("");
}

bool Press::refresh(){ // recuperation de la valeur de la pression
     int sensorValue;
     sensorValue = analogRead(_pin);   // Lecture de la valeur de la patte
     
     float volt = ((float)sensorValue*5)/1023;   // Conversion de la tension en pression (A modifier suite au calibrage)
     float pr = ((volt-0.2)/(0.045));
     
     _val[0] = String((int)(pr*100));             // Ecriture de la pression dans une string

}

/*void Press::getTrame(){ // Envoi de la trame
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
}*/
