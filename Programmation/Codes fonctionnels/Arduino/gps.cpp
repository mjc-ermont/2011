#include "gps.h"
#include "trame.h"
#include "defines.h"

GPS::GPS(){

}

bool GPS::init(){

}

bool GPS::refresh(){
  char current_char = 0;
  String table[20];
  int i = 0;
  
  if (Serial1.available() > 0){                     // On verifie qu'il y a des données a lire
    while (Serial1.read() != '$');                  // On attend le debut de la trame
    
    //Serial.println("Laulx");
    //delay(50);
    
    while (true){                                   // On lit toute la trame, sauf le checksum, et on la place dans un string
      current_char = Serial1.read();
      if (current_char == '*'){
        break;
      }
      
      if(current_char == ','){
        i++;
      }
        
      if ((current_char != -1) && (current_char != ',')){
        table[i] += current_char;
      }
    }
    
      if(table[0] == "GPRMC"){
        if(table[3].length() == 9){
          _lat_deg = table[3].substring(0, 2);
          _lat_min = table[3].substring(2);
        }
        
        if(table[5].length() == 10){
          _lon_deg = table[5].substring(0, 3);
          _lon_min = table[5].substring(3);
        }
      }
    //Serial.println("xLaul");
    return true;
  } else {
    return false;
  }
}

void GPS::getTrame(){
  for (byte i = 0 ; i < /*NB_VAL_GPS*/ 4 ; i++){
    String id_capt, val_capt;
    switch (i){
      case 0:
        id_capt = ID_VAL_LAT_DEG;
        val_capt = _lat_deg;
      break;
      case 1:
        id_capt = ID_VAL_LAT_MIN;
        val_capt = _lat_min;
      break;
      case 2:
        id_capt = ID_VAL_LON_DEG;
        val_capt = _lon_deg;
      break;
      case 3:
        id_capt = ID_VAL_LON_MIN;
        val_capt = _lon_min;
      break;
      default:
      break;
    }    
    String trame = "#$";
    trame += ID_CAPT_GPS;
    trame += "$";
    trame += id_capt;
    trame += "$";
    for (byte j = 0 ;  j < SIZE_VALUE - val_capt.length() ; j++) trame += "0";
    trame += val_capt;
    trame += "$";
    trame += String(get_checksum(trame), HEX);
    trame += "$@";
    /*for (byte k = 0 ; k < NB_REPET ; k++)*/ Serial.println(trame);
  }
}
