#include <SD.h>
#include "defines.h"
#include "sd_out.h"

SdOut::SdOut(){
  
}

bool SdOut::init(){          // Initialisation de la carte sd
  SD.begin(SD_CS_PIN);
  _file = SD.open("log.txt", FILE_WRITE);
}

void SdOut::writeQueue(){    // Eccriture de la file sur la sortie
  for(byte h = 0 ; h < queue.count() ; h++){    // Ecriture de la totalité de la file
    for (byte i = 0 ; i<NB_REPET ; i++){        // Plusieurs fois au cas ou le recepteur de receptionnerait pas les premieres fois
      _file.print(queue.pop());               // Ecriture de l'element courant
      _file.flush();                          // attente de la fin de l'ecriture
    }
  }
}
