#include <Arduino.h>
#include "defines.h"
#include "serial_out.h"
#include "debug.h"

SerialOut::SerialOut(){
  
}

bool SerialOut::init(){          // Initialisation du port serie (SERIAL_BAUDRATE defini dans defines.h)
  Serial.begin(SERIAL_BAUDRATE);
}

void SerialOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  //for(byte h = 0 ; h < queue.count() ; h++){    // Ecriture de la totalité de la file
    //char *trame = queue.pop();
    for (byte i = 0 ; i < NB_REPET ; i++){        // Plusieurs fois au cas ou le recepteur de receptionnerait pas les premieres fois
      Serial.println(trame);               // Ecriture de l'element courant
      Serial.flush();                          // attente de la fin de l'ecriture
    }
    //free(trame);
  //}
}
