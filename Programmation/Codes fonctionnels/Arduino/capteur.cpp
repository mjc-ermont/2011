#include <Arduino.h>
#include "capteur.h"
#include "defines.h"
#include "trame.h"
#include "debug.h"

Capteur::Capteur(const byte &id_capt, const byte &nb_val) : _id_capt(id_capt), _nb_val(nb_val) {
  _val = (char**) malloc(nb_val*sizeof(char*));
  for (byte i = 0 ; i < _nb_val ; i++){
    _val[i] = (char*)malloc(SIZE_VALUE + 2);
  }
}

void Capteur::addOut(Out *out){
  _out.push_back(out);  // Ajout de la sortie au tableau des sorties
  _nb_out++;
}

void Capteur::getTrame(){
  char *trame = (char*)malloc(21);          // Trame qui sera envoyee
  for (byte i = 0 ; i < _nb_val ; i++){
    debug("dtt");
    char buffer[10];
    strcpy(trame, "#$");
    /*Serial.print("Size : ");
    Serial.println(_out.size());*/
    debug("0");
    if (_id_capt < 10){                         // Pour toujours garder une taille constante
      strcat(trame, "0");
    }
    debug("1");
    itoa(_id_capt, buffer, 10);
    strcat(trame, buffer);                          // Ajout de l'ID du capteur
    debug("2");
    strcat(trame, "$");                              // separaeur
    itoa(i, buffer, 10);
    debug("3");
    strcat(trame, buffer);                                // No de la valeur
    strcat(trame, "$");                               // separaeur
    debug("4");
    for (byte j = 0 ;  j < ((byte)SIZE_VALUE) - ((byte)strlen(_val[i])) ; j++) {debug("b"); strcat(trame, "0");} // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    debug("5");
    strcat(trame, _val[i]);// Ajout de la valeur
    strcat(trame, "$");    // separaeur
    itoa(get_checksum(trame), buffer, 16);
    strcat(trame, buffer);  // Ajout du checksum
    strcat(trame, "$@");                             // separaeur + fin
 
    for (byte j = 0 ; j < _nb_out ; j++){   // envoi de la trame a toutes les sorties (d'ou le for)
      //_out[j]->addTrame(trame);                 // Ajout de la trame a la file d'envoi
      debug("debut_send");
      _out[j]->writeQueue(trame);                    // écriture sur la sortie de la file d'envoi 
      debug("fin_send");
    }
    debug("ftt");
  }
  //Serial.flush();
  free(trame);
}

Capteur::~Capteur(){
  for (byte i = 0 ; i < _nb_val ; i++){
    free(_val[i]);
  }
  free(_val);
}
