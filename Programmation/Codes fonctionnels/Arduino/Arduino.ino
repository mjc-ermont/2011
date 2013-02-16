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
 #include "sd_out.h"
 #include "debug.h"
 
 GPS gps = GPS(ID_CAPT_GPS);
 Accel accel = Accel(ID_CAPT_ACCEL);
 Hum hum = Hum(ID_CAPT_HUM);
 Press press = Press(ID_CAPT_PRESS, PIN_PRESS);
 Temp temp = Temp(ID_CAPT_TEMP, PIN_TEMP);
 SerialOut so = SerialOut();
 SdOut sd = SdOut();
 
 unsigned long timer;
 bool refreshed = false;
 
void setup() {
//#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
//#endif
    pinMode(SD_CS_PIN, OUTPUT);
/*  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Card failed, or not presente");
  }
  File _file = SD.open("sprof.txt", FILE_WRITE);
  if(!(_file)){
    Serial.println("------------------------");
  }
  _file.print("sdsdsd");
  _file.close();*/
  //Serial.print("jsdfjhfhfhfh");
    so.init();
    sd.init();
    pinMode(13, OUTPUT);
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
   accel.addOut(&sd);
   press.addOut(&sd);
   temp.addOut(&sd);
   hum.addOut(&sd);
   gps.addOut(&sd);
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
   debug("fff");
}
           
void loop(){
   //debug("d");
   if ( ((millis() - timer) >= (unsigned long)DELAY_SEND) && (refreshed) ){
     refreshed = false;
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
     debug("ft");
   } else if ( ((millis() - timer) >= (unsigned long)DELAY_REFRESH) && (!(refreshed)) ) {
     
     debug("dr");
     accel.refresh();
     debug("1");
     hum.refresh();
     debug("2");
     press.refresh();
     debug("3");
     temp.refresh();
     debug("fr");
     refreshed = true;
   } 
   if (Serial1.available() > 0){
     debug("drg");
     gps.refresh();
     debug("frg");
   }
   Serial.flush();
   //debug("f");
}

