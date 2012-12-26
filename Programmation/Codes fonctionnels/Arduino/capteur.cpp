#include <Arduino.h>
#include "capteur.h"
#include "defines.h"
#include "trame.h"

Capteur::Capteur(const byte &id_capt) : _id_capt(id_capt) {
  
}

void Capteur::addOut(Out &out){
  _out.push_back(out);  // Ajout de la sortie au tableau des sorties
}

void Capteur::getTrame(){
  String trame;         // Trame qui sera envoyee
  for (byte i = 0 ; i > _val.size() ; i++){
    trame = "#$";                              // debut +separaeur
    if (_id_capt < 10)                         // Pour toujours garder une taille constante
      trame += "0";
    trame += _id_capt;                         // Ajout de l'ID du capteur
    trame += "$";                              // separaeur
    trame += i;                                // No de la valeur
    trame += "$";                              // separaeur
    for (byte j = 0 ;  j < SIZE_VALUE - _val[i].length() ; j++) trame += "0"; // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    trame += _val[i];                          // Ajout de la valeur
    trame += "$";                              // separaeur
    trame += String(get_checksum(trame), HEX); // Ajout du checksum
    trame += "$@";                             // separaeur + fin
    for (int j = 0 ; j < _out.size() ; j++){   // envoi de la trame a toutes les sorties (d'ou le for)
      _out[j].addTrame(trame);                 // Ajout de la trame a la file d'envoi
      _out[j].writeQueue();                    // écriture sur la sortie de la file d'envoi 
    }
  }
}
