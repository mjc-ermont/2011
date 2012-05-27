 #include <string.h>
 #include "trame.h"
 #include "gps.h"

  
 void setup() {
   Serial.begin(9600);
   Serial1.begin(4800);
 }
 
 void loop(){
   String gps_1 = get_gps_1();
   String gps_2 = get_gps_2();
   
   Serial.print(gps_1);
   Serial.print(gps_2);
 }