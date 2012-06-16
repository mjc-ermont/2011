#include "gps.h"
#include "trame.h"
#include "defines.h"

GPS::GPS(){

}

bool GPS::init(){

}

bool GPS::refresh(){
  //Serial.println("Debut debut lol");
  
  int current_char = 0;
  int i = 0;
  char *trame_char, *cz;
  //Serial.println("Trolol bob");
  String table[40];
  //Sensor_out data;
  
  //Serial.println("Debut lol");
  
  /*data.id_capt = ID_CAPT_GPS;
  data.nb_values = NB_VAL_GPS;*/
  
  trame_char = (char*)malloc(100 * sizeof(char));
  
  if (Serial1.available()){                     // On verifie qu'il y a des données a lire
    while (Serial1.read() != '$');                  // On attend le debut de la trame
    
    //Serial.println("lol");
    
    while (true){                                   // On lit toute la trame, sauf le checksum, et on la place dans un string
      current_char = Serial1.read();
      if (((char)current_char == '*') || ((char)current_char == '$')){
        break;
      } else if (current_char != -1){
        trame_char[i] = (char)current_char;
        i++;
      }
    }
    
    trame_char[i] = 0;
    
    //Serial.println("Laulle");
    
    //trame.toCharArray(trame_char, 100); 
    
#if SERIAL_DEBUG
    Serial.println(trame_char);
#endif

    i = 0;

    //Serial.println("Xd");
    
    //cz = trame_char;

    while ((table[i] = strsep(&trame_char, ",")) != NULL){   // On isole chacune des parties de la trame reçue et on la stocke dans un tableau 
      Serial.println(table[i]);
      i++;
    }
    
    //Serial.println("xday.");
    
    free(trame_char);                               // On libere la memoire
    
    //Serial.println("Fin lol");
    
    return true;
  } else {
    return false;
  }
}
