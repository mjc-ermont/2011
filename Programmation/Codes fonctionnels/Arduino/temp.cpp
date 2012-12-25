#include "temp.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>

Temp::Temp(){
}

bool Temp::init(){ // Initialisation du capteur
}

bool Temp::refresh(){  // Recuperation de la temperature
 double Temp;
 int RawADC = analogRead(9);  // Lecture de la tension
 Temp = log(((10240000/RawADC) - 10000));                                              // Conversion de la tension en temperature
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 
 _temp = String((int)(Temp*100)); // Formatage de la valeur pour l'envoi
}

void Temp::getTrame(){  // Evoi de la trame
    String trame = "#$";
    trame += ID_CAPT_TEMP;
    trame += "$0$";
    for (byte j = 0 ;  j < SIZE_VALUE - _temp.length() ; j++) trame += "0";
    trame += _temp;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    for (byte k = 0 ; k < NB_REPET ; k++) Serial.print(trame);
    Serial.flush();
}
