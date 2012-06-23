 #include "trame.h"
 #include "gps.h"
 #include "defines.h"

 GPS gps = GPS();
  
 void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
  
   Serial1.begin(GPS_BAUDRATE);
 }
 
 void loop(){
#if SERIAL_DEBUG
   //Serial.println();
#endif
 }
 
 void serialEvent1(){      // Quand il y a quelquechose a lire sur le port serie, on rafraichit les donnees du GPS
   gps.refresh();
 }
