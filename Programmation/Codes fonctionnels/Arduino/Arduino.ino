 #include "Wire.h"
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "pression.h"
 #include "temp.h"
 #include "serial_out.h"
 
 GPS gps = GPS();
 Accel accel = Accel();
 Hum hum = Hum();
 Press press = Press();
 Temp temp = Temp();
 SerialOut so = SerialOut();;
 unsigned long timer;
 
  
void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   press.init();
   gps.init();
   accel.init();
   hum.init();
   temp.init();
   accel.addOut(so);
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
}
           
void loop(){
   //Serial.println("d");
   if ((millis() - timer) >= (unsigned long)1000){
     
     //Serial.println("dt");
     gps.getTrame();
     Serial.flush();
     accel.getTrame();
     Serial.flush();
     hum.getTrame();
     Serial.flush();
     press.getTrame();
     Serial.flush();
     temp.getTrame();
     Serial.flush();
     timer = millis();
     //Serial.println("ft");
 } else if ((millis() - timer) >= (unsigned long)800) {
     //Serial.println("dr");
     accel.refresh();
     hum.refresh();
     press.refresh();
     temp.refresh();
     //Serial.println("fr");
   } else if (Serial1.available() > 0){
     //Serial.println("drg");
     gps.refresh();
     //Serial.println("frg");  
 }
   //Serial.println("f");
}

