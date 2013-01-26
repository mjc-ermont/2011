#include "capteur_analog.h"

CapteurAnalog::CapteurAnalog(byte id, int pin) : Capteur::Capteur(id, 1){
  _pin = pin;
}
