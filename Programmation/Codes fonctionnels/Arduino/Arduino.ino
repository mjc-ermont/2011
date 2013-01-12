 #include <Wire.h>
 #include <SD.h>
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "pression.h"
 #include "temp.h"
 #include "serial_out.h"
 #include "debug.h"
 
 GPS gps = GPS(ID_CAPT_GPS);
 Accel accel = Accel(ID_CAPT_ACCEL);
 Hum hum = Hum(ID_CAPT_HUM);
 Press press = Press(ID_CAPT_PRESS, PIN_PRESS);
 Temp temp = Temp(ID_CAPT_TEMP, PIN_TEMP);
 SerialOut so = SerialOut();
 unsigned long timer;
 
  
void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   Serial.println("ddd");
   press.init();
   Serial.println("111");
   gps.init();
   Serial.println("222");
   accel.init();
   Serial.println("333");
   hum.init();
   Serial.println("444");
   temp.init();
   Serial.println("mmm");
   accel.addOut(so);
   press.addOut(so);
   temp.addOut(so);
   hum.addOut(so);
   gps.addOut(so);
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
   Serial.println("fff");
}
           
void loop(){
   debug("d");
   if ((millis() - timer) >= (unsigned long)DELAY_SEND){
     debug("dt");
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
     debug("ft");
   } else if ((millis() - timer) >= (unsigned long)DELAY_REFRESH) {
     debug("dr");
     accel.refresh();
     hum.refresh();
     press.refresh();
     temp.refresh();
     debug("fr");
   } else if (Serial1.available() > 0){
     debug("drg");
     gps.refresh();
     debug("frg");
   }
   debug("f");
}

