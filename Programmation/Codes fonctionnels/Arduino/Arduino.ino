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
 bool refreshed = false;
 
void setup() {
    so.init();
    pinMode(13, OUTPUT);
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   debug("ddd");
   press.init();
   debug("111");
   gps.init();
   debug("222");
   accel.init();
   debug("333");
   hum.init();
   debug("444");
   temp.init();
   debug("mmm");
   accel.addOut(&so);
   press.addOut(&so);
   temp.addOut(&so);
   hum.addOut(&so);
   gps.addOut(&so);
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
   debug("fff");
}
           
void loop(){
   //debug("d");
   if ((millis() - timer) >= (unsigned long)DELAY_SEND){
     debug("dt");
     gps.getTrame();
     Serial.flush();
     debug("1");
     accel.getTrame();
     Serial.flush();
     debug("2");
     hum.getTrame();
     Serial.flush();
     debug("3");
     press.getTrame();
     Serial.flush();
     debug("4");
     temp.getTrame();
     Serial.flush();
     timer = millis();
     refreshed = false;
     debug("ft");
   } else if ( ((millis() - timer) >= (unsigned long)DELAY_REFRESH) && (!(refreshed)) ) {
     refreshed = true;
     debug("dr");
     accel.refresh();
     debug("1");
     hum.refresh();
     debug("2");
     press.refresh();
     debug("3");
     temp.refresh();
     debug("fr");
   } 
   if (Serial1.available() > 0){
     debug("drg");
     gps.refresh();
     debug("frg");
   }
   //debug("f");
}

