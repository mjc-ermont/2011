 #include "trame.h"
 #include "gps.h"
 #include "defines.h"

 GPS gps = GPS();
 unsigned long timer;
  
 void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
  
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
 }
 
 void loop(){
   //Serial.println("Lolxx");
   if ((millis() - timer) >= (unsigned long)1000){
       Serial.println(millis() - timer);
       timer = millis();
       gps.getTrame();
   }
   if (Serial1.available() > 0){
     gps.refresh();
   }
   //Serial.println("xxLol");
 }
 
 void serialEvent1(){      // Quand il y a quelquechose a lire sur le port serie, on rafraichit les donnees du GPS
   //Serial.println("Laulle");
   
   /*gps.refresh();
   //Serial.println("xxLaul");
   //delay(50);
   gps.getTrame();
   //Serial.println("Cyparlol danslesetoiles");*/
 }
