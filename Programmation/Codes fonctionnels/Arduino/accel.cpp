#include "accel.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>
#include <Wire.h>

Accel::Accel(){
  
}

bool Accel::init(){
  Wire.begin();
  delay(100);
  _accel.set_bw(ADXL345_BW_12);
  _accel.powerOn();
}

bool Accel::refresh(){
  double acc_data[3];
  float avg = 0;
  _accel.get_Gxyz(acc_data);
  
  for(int i = 0; i < 3; i++){
    avg += (float)acc_data[i] * (float)acc_data[i];
  }
  
  _avg = String((int)(100*sqrt(avg)));
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
    for (int i = 0 ; i < _out.size() ; i++){
      _out[i].addTrame(trame);
      _out[i].writeQueue();
    }
}
