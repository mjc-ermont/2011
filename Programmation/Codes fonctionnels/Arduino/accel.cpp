#include "accel.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>
#include <Wire.h>
#include "capteur.h"

Accel::Accel(const byte &id_capt) : Capteur::Capteur(id_capt){

}

bool Accel::init(){ // methode d'iniialisation de l'accelerometre
  Wire.begin();                  // initialisation de la bibliotheque I2C
  delay(100);
  _accel.set_bw(ADXL345_BW_12);  // Allumage de l'accelerometre
  _accel.powerOn();
  _val.push_back("");
}

bool Accel::refresh(){ // methode de recuperation des donnees de l'accelerometre
  float acc_data[3];             // Tableau des trois composantes du vecteur d'acceleration
  float avg = 0;                 // Norme du vecteur d'acceleration
  
  _accel.get_Gxyz((double*)acc_data);     // recuperation des valeurs de l'accelerometre
  
  for(int i = 0; i < 3; i++){    // Calcul de la norme du vecteur d'acceleration
    avg += (float)acc_data[i] * (float)acc_data[i];
  }
  
  _val[0] = String((int)(100*sqrt(avg)));
  //Serial.println((int)(avg*100));
}

/*void Accel::getTrame(){ // methode d'envoi de la trame
    String trame = "#$";                     // debut +separaeur
    trame += ID_CAPT_ACCEL;                  // Ajout de l'ID du capteur
    trame += "$0$";                          // separaeur + ID valeur + separateur
    for (byte j = 0 ;  j < SIZE_VALUE - _avg.length() ; j++) trame += "0"; // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    trame += _avg;                           // Ajout de la valeuts
    trame += "$";                            // separaeur
    trame += String(get_checksum(trame), HEX);// Ajout du checksum
    trame += "$@";                           // separaeur + fin
    for (int i = 0 ; i < _out.size() ; i++){ // envoi de la trame a toutes les sorties (d'ou le for)
      _out[i].addTrame(trame);               // Ajout de la trame a la file d'envoi
      _out[i].writeQueue();                  // écriture sur la sortie de la file d'envoi 
    }
}*/
