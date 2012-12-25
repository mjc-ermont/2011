#include "out.h"

Out::Out(){
   
}

void Out::addTrame(String trame){ // Ajout d'une sortie a la file d'attente
  queue.push(String(trame));
}
