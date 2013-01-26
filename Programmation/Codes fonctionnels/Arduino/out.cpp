#include "out.h"

Out::Out(){
  //queue = QueueArray<String>();  
}

void Out::addTrame(char *trame){ // Ajout d'une sortie a la file d'attente
  Serial.print("Trame :");
  Serial.println(trame);
  Serial.flush();
  queue.push(trame);
  Serial.print("Trame :");
  Serial.println(trame);
}
