 #include "Wire.h"
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"

 GPS gps = GPS();
 Accel accel = Accel();
 unsigned long timer;
  
 void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   gps.init();
   accel.init();
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
 }
 
 void loop(){
   if ((millis() - timer) >= (unsigned long)1000){
     Serial.println(millis() - timer);
     timer = millis();
     gps.getTrame();
     accel.getTrame();
   } else if (Serial1.available() > 0){
     gps.refresh();
   } else if ((millis() - timer) >= (unsigned long)800) {
     accel.refresh();
   }
 }

