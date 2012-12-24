#include "defines.h"
#include "serial_out.h"

SerialOut::SerialOut(){
  
}

bool SerialOut::init(){
  Serial.begin(SERIAL_BAUDRATE);
}

void SerialOut::writeQueue(){
  for(int h = 0 ; h < queue.count() ; h++){ 
    for (int i = 0 ; i<NB_REPET ; i++){
      Serial.print(queue.pop());
      Serial.flush();
    }
  }
}
