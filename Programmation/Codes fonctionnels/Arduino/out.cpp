#include "out.h"

Out::Out(){
  //queue = QueueArray<String>();  
}

void Out::addTrame(String &trame){ // Ajout d'une sortie a la file d'attente
  queue.push(trame);
}
