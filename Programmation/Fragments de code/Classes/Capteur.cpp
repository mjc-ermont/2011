#include "Capteur.h"

Capteur::Capteur(){

}

bool Capteur::flush(){
   return fonctionOfTheDeadQuiEnverrasLaTrameEtQuiRetourneraSiCaAMarcheOuNonEnBoolean(trame);
}