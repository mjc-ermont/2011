#include <Arduino.h>
#include "capteur.h"

Capteur::Capteur(){
  
}

void Capteur::addOut(Out &out){
  _out.push_back(out);
}
