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
   if (Serial1.available()){
     //Serial.println("available laulle");
     //gps.refresh();
   }
#endif
 }
 
 void serialEvent1(){      // Quand il y a quelquechose a lire sur le port serie, on rafraichit les donnees du GPS
   //Serial.println("Debut debut debut lol");
   gps.refresh();
   //Serial.println("Fin lol");
 }
