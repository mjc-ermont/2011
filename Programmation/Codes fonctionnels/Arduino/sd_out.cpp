#include <SD.h>
#include "defines.h"
#include "sd_out.h"

SdOut::SdOut(){
  
}

bool SdOut::init(){          // Initialisation de la carte sd
  pinMode(SD_CS_PIN, OUTPUT);
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Card failed, or not present");
  }
  
  
  //_file = &file;
  /*if(!(*_file)){
    Serial.println("Can't write to file");
  }*/
  //_file.print("lodledfkjsdhfkdsjh");
  //_file.close();
}

void SdOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  File file = SD.open("slog.txt", FILE_WRITE);
  //for(byte h = 0 ; h < queue.count() ; h++){    // Ecriture de la totalité de la file
    for (byte i = 0 ; i<NB_REPET ; i++){        // Plusieurs fois au cas ou le recepteur de receptionnerait pas les premieres fois
      if(!(file)){
        Serial.println("Can't write to file");
      }
      //Serial.println("ljsfhfgsfdhjdfhjghjg");
      file.print(trame);                     // Ecriture de l'element courant
      file.flush();                          // attente de la fin de l'ecriture
    }
  //}
  file.close();
}
