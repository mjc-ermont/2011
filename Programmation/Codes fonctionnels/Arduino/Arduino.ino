 #include "Wire.h"
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"

 GPS gps = GPS();
 Accel accel = Accel();
 Hum hum = Hum();
 unsigned long timer;
 
  
 void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   gps.init();
   accel.init();
   hum.init();
   
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
 }
           
 void loop(){
   if ((millis() - timer) >= (unsigned long)1000){
     
     //Serial.println(millis() - timer);
     timer = millis();
     gps.getTrame();
     accel.getTrame();
     hum.getTrame();
   } else if ((millis() - timer) >= (unsigned long)800) {
     accel.refresh();
     hum.refresh();
   } else if (Serial1.available() > 0){
     gps.refresh();
   }
 }

