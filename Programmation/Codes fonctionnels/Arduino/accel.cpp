#include "accel.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>
#include <Wire.h>

Accel::Accel(){
  
}

bool Accel::init(){
  Wire.begin();
  _accel.set_bw(ADXL345_BW_12);
}

bool Accel::refresh(){
  double acc_data[3];
  float avg = 0;
  _accel.get_Gxyz(acc_data);
  
  for(int i = 0; i < 3; i++){
    avg += (float)acc_data[i] * (float)acc_data[i];
    Serial.println(acc_data[i]);
    Serial.println(_accel.status);
  }
  
  avg = sqrt(avg);
  //Serial.println((int)(avg*100));
}

void Accel::getTrame(){
    String trame = "#$";
    trame += ID_CAPT_ACCEL;
    trame += "$0$";
    for (byte j = 0 ;  j < SIZE_VALUE - _avg.length() ; j++) trame += "0";
    trame += _avg;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    for (byte k = 0 ; k < NB_REPET ; k++) Serial.println(trame);
    Serial.flush();
}
