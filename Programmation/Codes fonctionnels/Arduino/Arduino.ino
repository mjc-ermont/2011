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
   if ((millis() - timer) >= (unsigned long)1000){
       Serial.println(millis() - timer);
       timer = millis();
       gps.getTrame();
   } else if (Serial1.available() > 0){
     gps.refresh();
   }
 }

