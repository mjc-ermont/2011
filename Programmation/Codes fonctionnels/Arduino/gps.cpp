#include "gps.h"
#include "trame.h"


char linea[300] = "";
int conta=0;


String get_gps_1() {
 int indices[13];
 int bien=0;
 int byteGPS=-1;
 int cont=0;
 char comandoGPR1[7] = "$GPRMC";
 String trame;
 String temp_trame;
 String out_trame = "";
 char atrame[50], mtrame[50], temp_trame_array[50];
 int angle;
 double minute;
 int lmaxtrame;
  while (Serial1.available() > 0){
     byteGPS=Serial1.read();         // Read a byte of the serial port
     if (byteGPS == -1) {           // See if the port is empty yet
       return String("");
     } else {
       linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
       conta++;                      
       //Serial.write(byteGPS); 
       if (byteGPS==13){            // If the received byte is = to 13, end of transmission
         cont=0;
         bien=0;
         for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
           if (linea[i]==comandoGPR1[i-1]){
             bien++;
           }
         }
         if(bien==6){               // If yes, continue and process the data
           for (int i=0;i<300;i++){
             if (linea[i]==','){    // check for the position of the  "," separator
               indices[cont]=i;
             cont++;
           }
             if (linea[i]=='*'){    // ... and the "*"
               indices[12]=i;
             cont++;
           }
         }
         for (int i=0;i<12;i++){
             /*switch(i){
               case 0 :Serial.print("Time in UTC (HhMmSs): ");break;
               case 1 :Serial.print("Status (A=OK,V=KO): ");break;
               case 2 :Serial.print("Latitude: ");break;
               case 3 :Serial.print("Direction (N/S): ");break;
               case 4 :Serial.print("Longitude: ");break;
               case 5 :Serial.print("Direction (E/W): ");break;
               case 6 :Serial.print("Velocity in knots: ");break;
               case 7 :Serial.print("Heading in degrees: ");break;
               case 8 :Serial.print("Date UTC (DdMmAa): ");break;
               case 9 :Serial.print("Magnetic degrees: ");break;
               case 10 :Serial.print("(E/W): ");break;
               case 11 :Serial.print("Mode: ");break;
               case 12 :Serial.print("Checksum: ");break;
             }*/
               for (int j=indices[i];j<(indices[i+1]-1);j++){
                 trame += linea[j+1];
               }
               trame.toCharArray(mtrame, 50);
               for (int i = 0 ; i<50 ; i++){
                 atrame[i] = 0;
               }
               if(i == 2){
                 trame.toCharArray(atrame, 3);
                 temp_trame += "#$00$00$";
                 lmaxtrame = 8;
                 while((lmaxtrame - strlen(atrame)) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 temp_trame += atrame;
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";

                 temp_trame = "#$00$01$";
                 lmaxtrame = 8;
                 while((lmaxtrame - strlen(&mtrame[2])) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 temp_trame += &mtrame[2];
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";

               } else if (i==4) {
                 trame.toCharArray(atrame, 3);
                 temp_trame += "#$00$02$";
                 lmaxtrame = 8;
                 while((lmaxtrame - strlen(atrame)) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 temp_trame += atrame;
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";

                 temp_trame += "#$00$03$";
                 lmaxtrame = 8;


                 while((lmaxtrame - strlen(&mtrame[2])) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 minute = atof(&mtrame[2]);
                 temp_trame += &mtrame[2];
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";

               } else if (i == 6){
                 temp_trame = "#$00$04$";
                 lmaxtrame = 8;
                 while((lmaxtrame - trame.length()) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 temp_trame += trame;
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";
               } else if (i == 0){
                 temp_trame = "#$00$05$";
                 lmaxtrame = 8;
                 while((lmaxtrame - trame.length()) > 0){
                   temp_trame += '0';
                   lmaxtrame--;
                 }
                 temp_trame += trame;
                 temp_trame += "$";
                 temp_trame.toCharArray(temp_trame_array, 50);
                 temp_trame += String(get_checksum(temp_trame_array), HEX);
                 temp_trame += "@\n";
                 out_trame += temp_trame;
                 temp_trame="";
               }

               trame="";
             }

           }
         conta=0;                    // Reset the buffer
         
        Serial.print("Buffer : ");
        Serial.println(linea);
        for (int i=0;i<300;i++){    //  
           linea[i]=' ';         
         }       
       }
     }

}
Serial.println("Fini lol");
     return out_trame;
     //out_trame="";
   }
   
String get_gps_2() {
  int indices[13];
  int bien=0;
 int byteGPS=-1;
  int cont=0;
  char comandoGPR2[7] = "$GPGGA";
  String trame;
  String temp_trame;
  String out_trame = "";
  char atrame[50], mtrame[50], temp_trame_array[50];
  int angle;
  double minute;
  int lmaxtrame;
  while (Serial1.available() > 0){
  byteGPS=Serial1.read();         // Read a byte of the serial port
  if (byteGPS == -1) {           // See if the port is empty yet
    return String("");
  } else {
    linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
    conta++;                      
    //Serial.write(byteGPS); 
    if (byteGPS==13){            // If the received byte is = to 13, end of transmission
      cont=0;
      bien=0;
      for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
        if (linea[i]==comandoGPR2[i-1]){
          bien++;
        }
      }
      if(bien==6){               // If yes, continue and process the data
        for (int i=0;i<300;i++){
          if (linea[i]==','){    // check for the position of the  "," separator
            indices[cont]=i;
          cont++;
        }
          if (linea[i]=='*'){    // ... and the "*"
            indices[12]=i;
          cont++;
        }
      }
      for (int i=0;i<12;i++){
            for (int j=indices[i];j<(indices[i+1]-1);j++){
              trame += linea[j+1];
            }
            trame.toCharArray(mtrame, 50);
            for (int i = 0 ; i<50 ; i++){
              atrame[i] = 0;
            }
            if (i == 8){
              temp_trame = "#$00$06$";
              lmaxtrame = 8;
              while((lmaxtrame - trame.length()) > 0){
                temp_trame += '0';
                lmaxtrame--;
              }
              temp_trame += trame;
              temp_trame += "$";
              temp_trame.toCharArray(temp_trame_array, 50);
              temp_trame += String(get_checksum(temp_trame_array), HEX);
              temp_trame += "@\n";
              out_trame += temp_trame;
              temp_trame="";
            }
             trame="";
          }
         }
      conta=0;
        Serial.print("Buffer : ");
        Serial.println(linea);      // Reset the buffer
      for (int i=0;i<300;i++){    //  
        linea[i]=' ';         
      }       
    }
  }
  }
  Serial.println("Fini lol");
  return out_trame;
  //out_trame="";
}

GPS::GPS(){

}

bool GPS::init(){

}

bool GPS::refresh(){
  char current_char = 0;
  char **trame_table = NULL, trame_char[100] = "";
  String trame = "";
  if (Serial1.available() > 0){
    while (Serial1.read() != '$');
    while (true){
      current_char = Serial1.read();
      if ((current_char == '*') /*|| (current_char == -1)*/){
        break;
      }
      if (current_char != -1){
        trame += current_char;
      }
    }
    //Serial.println(trame);
    trame.toCharArray(trame_char, 100);
    trame_table = split(trame_char, ",", 0);
    for (int i = 0 ; i < sizeof(trame_table) ; i++){
      Serial.println(trame_table[i]);
    }
    free(trame_table);
    return true;
  } else {
    //Serial.print("Ca commence LOL !!!!!!!!!!!");
    return false;
  }
}
