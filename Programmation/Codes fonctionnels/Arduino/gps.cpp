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
  Sensor_out data;
  
  data.id_capt = ID_CAPT_GPS;
  data.nb_values = NB_VAL_GPS;
  data.values = (Value*)malloc(NB_VAL_GPS * sizeof(Value));
  
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
          Serial.print("deg : ");
          Serial.println(table[3].substring(0, 2));
          Serial.print("min : ");
          Serial.println(table[3].substring(2));
          Serial.println();
        }
        
        if(table[5].length() == 10){
          Serial.print("deg : ");
          Serial.println(table[5].substring(0, 3));
          Serial.print("min : ");
          Serial.println(table[5].substring(3));
          Serial.println();
        }
      }
    
    return true;
  } else {
    return false;
  }
}
