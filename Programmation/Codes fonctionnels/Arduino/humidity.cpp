#include "humidity.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>
#include <Wire.h>

Hum::Hum(){
}

bool Hum::init(){
  Wire.begin();
}

bool Hum::refresh(){
    double Humidity;
    double Temperature;

  
    Wire.beginTransmission(HYT371_ADDR);
    Wire.write((uint8_t)0);
    Wire.available();
    int Ack = Wire.read(); // read a byte

    Wire.endTransmission();
    delay(100);
    
    // READ DATA from here on
    Wire.beginTransmission(HYT371_ADDR);
    Wire.requestFrom(HYT371_ADDR,4);  //Reade 1 byte
    Wire.available();
    int b1 = Wire.read(); // read a byte
    int b2 = Wire.read(); // read a byte
    int b3 = Wire.read(); // read a byte
    int b4 = Wire.read(); // read a byte
    Wire.write((uint8_t)0); //NACK

    // combine the bits
    int RawHumidBin = b1 << 8 | b2;
    // compound bitwise to get 14 bit measurement first two bits
    // are status/stall bit (see intro text)
    RawHumidBin =  (RawHumidBin &= 0x3FFF);
    Humidity = 100.0/pow(2,14)*RawHumidBin;

    b4 = (b4 &= 0x3F); //Mask away 2 least sign. bits see HYT 221 doc
    int RawTempBin = b3 << 6 | b4;
    Temperature = 165.0/pow(2,14)*RawTempBin-40;

    Wire.endTransmission();
    
    _hum = String((int)(Humidity*100));
    _temp = String((int)(Temperature*100));
    
    //Serial.println(Humidity);

}

void Hum::getTrame(){
    String trame = "#$";
    trame += ID_CAPT_HUM;
    trame += "$0$";
    for (byte j = 0 ;  j < SIZE_VALUE - _hum.length() ; j++) trame += "0";
    trame += _hum;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    for (byte k = 0 ; k < NB_REPET ; k++) Serial.print(trame);
    Serial.flush();
    
    trame = "#$";
    trame += ID_CAPT_HUM;
    trame += "$1$";
    for (byte j = 0 ;  j < SIZE_VALUE - _temp.length() ; j++) trame += "0";
    trame += _temp;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    for (byte k = 0 ; k < NB_REPET ; k++) Serial.print(trame);
    Serial.flush();
    
}
