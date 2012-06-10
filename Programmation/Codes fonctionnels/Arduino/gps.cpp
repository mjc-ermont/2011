#include "gps.h"
#include "trame.h"
#include "defines.h"

GPS::GPS(){

}

bool GPS::init(){

}

bool GPS::refresh(){
  char current_char = 0;
  char *trame_char = NULL;
  String trame = "", table[20];
  Sensor_out data;
  
  data.id_capt = ID_CAPT_GPS;
  data.nb_values = NB_VAL_GPS;
  
  trame_char = (char*)malloc(100 * sizeof(char));
  
  if (Serial1.available() > 0){                     // On verifie qu'il y a des données a lire
    while (Serial1.read() != '$');                  // On attend le debut de la trame
    
    while (true){                                   // On lit toute la trame, sauf le checksum, et on la place dans un string
      current_char = Serial1.read();
      if (current_char == '*'){
        break;
      }
      if (current_char != -1){
        trame += current_char;
      }
    }
    
#if SERIAL_DEBUG
    Serial.println(trame);
#endif

    trame.toCharArray(trame_char, 100);             // On convertit l'objet String en chaine de caracteres pour pouvoir le sparer

    byte i = 0;
    while ((table[i] = strsep(&trame_char, ",")) != NULL){   // On isole chacune des parties de la trame reçue et on la stocke dans un tableau 
      i++;
    }
    
#if SERIAL_DEBUG
    for (byte j = 0 ; j <= i ; j++){
      Serial.println(table[j]);
    }
#endif

    free(trame_char);                               // On libere la memoire
    trame = "";
    
    return true;
  } else {
    return false;
  }
}
