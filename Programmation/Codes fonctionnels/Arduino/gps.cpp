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
    
    while (true){                                   // On lit toute la trame, sauf le checksum, et on la place dans un string
      current_char = Serial1.read();
      if (current_char == '*'){
        break;
      }
      if(current_char == ','){
#if SERIAL_DEBUG        
        //Serial.println(table[i]);
#endif
        i++;
      }
        
      if ((current_char != -1) && (current_char != ',')){
        table[i] += current_char;
      }
    }
    

      if(table[0] == "GPRMC"){
        if(table[3].length() == 9){
          _lat_deg = table[3].substring(0, 2);
          //Serial.println(_lat_deg);
          _lat_min = table[3].substring(2);
          //Serial.println(_lat_min);
        }
        
        if(table[5].length() == 10){
          _lon_deg = table[5].substring(0, 3);
          //Serial.println(_lon_deg);
          _lon_min = table[5].substring(3);
          //Serial.println(_lon_min);
        }
      }
    
    return true;
  } else {
    return false;
  }
}

void GPS::getTrame(){
/*  Serial.println("Laulle");*/
  Serial.println(_lat_deg);
  Serial.println(_lat_min);
  Serial.println(_lon_deg);
  Serial.println(_lon_min);
}
