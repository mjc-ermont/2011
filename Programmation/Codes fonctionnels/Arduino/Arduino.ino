 #include "Wire.h"
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "pression.h"
 #include "temp.h"
 
 GPS gps = GPS();
 Accel accel = Accel();
 Hum hum = Hum();
 Press press = Press();
 Temp temp = Temp();
 unsigned long timer;
 
  
void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   press.init();
   gps.init();
   accel.init();
   hum.init();
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
     press.getTrame();
     temp.getTrame();
   } else if ((millis() - timer) >= (unsigned long)800) {
     accel.refresh();
     hum.refresh();
     press.refresh();
     temp.refresh();
   } else if (Serial1.available() > 0){
     gps.refresh();
   }
}

