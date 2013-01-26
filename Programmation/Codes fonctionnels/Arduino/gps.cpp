#include "gps.h"
#include "trame.h"
#include "defines.h"
#include "debug.h"

GPS::GPS(const byte &id) : Capteur::Capteur(id){

}

bool GPS::init(){
  _val.push_back("");
  _val.push_back("");
  _val.push_back("");
  _val.push_back("");
  _val.push_back("");
}

bool GPS::refresh(){
  //Serial.println("Debut");
  char current_char = 0;                            // Variable contenant le byte qui vient d'être lu depuis le GPS
  String table[20];                                 // tableau contenant la trame complète envoyée par le GPS
  byte i = 0;
  
  if (Serial1.available() > 0){                     // On verifie qu'il y a des données a lire
    while (Serial1.read() != '$');                  // On attend le debut de la trame
    int timer = millis();
    while (true){                                   // On lit toute la trame, sauf le checksum, et on la place dans un string
      //debug("w");
      if ((millis() - timer) > 1000)
        break;
      current_char = Serial1.read();
      if (current_char == '*'){                     // Arret de la boucle quand on arrive a la fin
        break;
      }
      
      if(current_char == ','){                      // si on rencontre une virgule, on passe a la valeur suivante
        //Serial.println(table[i]);
        i++;
      }
        
      if ((current_char != -1) && (current_char != ',')){ // Si la donnée lue est une valeur acceptable, on l'ajoute a la chaine
        table[i] += current_char;
      }
    }
    
    if(table[0] == "GPRMC"){                            // On trie les données recues : Si la trame recue est une trame GPRMC ...
       
      _val[ID_VAL_UTIME] = table[1];                                // ... On en extrait le temps, ...
      
      if(table[3].length() == 9){                       // ... la latitude et la longitude (si la valeur a la bonne longueur) ...
        _val[ID_VAL_LAT_DEG] = table[3].substring(0, 2);
        _val[ID_VAL_LAT_MIN] = table[3].substring(2);
      }
      
      if(table[5].length() == 10){
        _val[ID_VAL_LON_DEG] = table[5].substring(0, 3);
        _val[ID_VAL_LON_MIN] = table[5].substring(3);
      }
      _val[ID_VAL_VIT] = table[7];                                  // ... et la vitesse
      //Serial.println(freeMemory());
    }
    return true;
  } else {
    return false;
  }
}

/*void GPS::getTrame(){
  debug("dtg");
  for (byte i = 0 ; i < 6 ; i++){          // Pour chaque valeur envoyée par le GPS
    String id_capt, val_capt;                             // variables contenant respectivement l'id et la valeur de la donnee du GPS en cours d'envoi
    switch (i){                                           // On attribue a la variable temporaire la valeur et l'ID de la donnee du GPS en cours d'envoi
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
      case 4:
        id_capt = ID_VAL_VIT;
        val_capt = _vit;
      break;
      case 5:
        id_capt = ID_VAL_UTIME;
        val_capt = _utime;
      break;
      default:
      break;
    }
    debug("mtg");
    String trame = "#$";      // Debut + separateur
    trame += ID_CAPT_GPS;     // ID du capteur
    trame += "$";             // Separateur
    trame += id_capt;         // ID de la valeur en cours d'envoi
    trame += "$";             // Separateur
    for (byte j = 0 ;  j < SIZE_VALUE - val_capt.length() ; j++) trame += "0"; // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    trame += val_capt;        // Valeur du capteur a envoyer
    trame += "$";             // Separateur
    trame += String(get_checksum(trame), HEX); // Checksum
    trame += "$@";            // Separateur + fin
    for (byte k = 0 ; k < NB_REPET ; k++) { // repetition et envoi de la trame
      Serial.print(trame);
      Serial.flush();
    }
    debug("ftg");
  }
}*/
