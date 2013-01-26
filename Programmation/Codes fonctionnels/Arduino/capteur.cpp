#include <Arduino.h>
#include "capteur.h"
#include "defines.h"
#include "trame.h"
#include "debug.h"

Capteur::Capteur(const byte &id_capt) : _id_capt(id_capt) {
  
}

void Capteur::addOut(Out *out){
  _out.push_back(out);  // Ajout de la sortie au tableau des sorties
}

void Capteur::getTrame(){
  for (byte i = 0 ; i < _val.size() ; i++){
    char *trame = (char*)malloc(21);          // Trame qui sera envoyee
    char buffer[10];
    strcpy(trame, "#$");
    /*Serial.print("Size : ");
    Serial.println(_out.size());*/
    debug("0");
    if (_id_capt < 10)                         // Pour toujours garder une taille constante
    strcat(trame, "0");
    debug("1");
    itoa(_id_capt, buffer, 10);
    strcat(trame, buffer);                          // Ajout de l'ID du capteur
    debug("2");
    strcat(trame, "$");                              // separaeur
    itoa(i, buffer, 10);
    strcat(trame, buffer);                                // No de la valeur
    strcat(trame, "$");                              // separaeur
    for (byte j = 0 ;  j < SIZE_VALUE - _val[i].length() ; j++) strcat(trame, "0"); // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    _val[i].toCharArray(buffer, 10);                          
    strcat(trame, buffer);// Ajout de la valeur
    strcat(trame, "$");    // separaeur
    itoa(get_checksum(trame), buffer, 16);
    strcat(trame, buffer);  // Ajout du checksum
    strcat(trame, "$@");                             // separaeur + fin
 
    for (byte j = 0 ; j < _out.size() ; j++){   // envoi de la trame a toutes les sorties (d'ou le for)
      _out[j]->addTrame(trame);                 // Ajout de la trame a la file d'envoi
      debug("debut_send");
      _out[j]->writeQueue();                    // écriture sur la sortie de la file d'envoi 
      debug("fin_send");
    }
    
  }
}
