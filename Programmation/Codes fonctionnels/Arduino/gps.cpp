#include <string.h>

int byteGPS=-1;
char linea[300] = "";
char comandoGPR1[7] = "$GPRMC";
char comandoGPR2[7] = "$GPGGA";
int cont=0;
int bien=0;
int conta=0;
int indices[13];

String get_gps_1() {
 String trame;
 String temp_trame;
 String out_trame = "";
 char atrame[50], mtrame[50], temp_trame_array[50];
 int angle;
 double minute;
 int lmaxtrame;

     byteGPS=Serial1.read();         // Read a byte of the serial port
     if (byteGPS == -1) {           // See if the port is empty yet
       delay(50); 
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

                 temp_trame = "#$00$02$";
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
                 temp_trame += "#$00$03$";
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

                 temp_trame += "#$00$04$";
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
               } else if (i == 0){
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
         conta=0;                    // Reset the buffer
         for (int i=0;i<300;i++){    //  
           linea[i]=' ';         
         }       
       }
     }
     return out_trame;
     //out_trame="";
   }
   
String get_gps_2() {
  String trame;
  String temp_trame;
  String out_trame = "";
  char atrame[50], mtrame[50], temp_trame_array[50];
  int angle;
  double minute;
  int lmaxtrame;
  
  byteGPS=Serial1.read();         // Read a byte of the serial port
  if (byteGPS == -1) {           // See if the port is empty yet
    delay(50); 
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
            if (i == 8){
              temp_trame = "#$00$07$";
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
      for (int i=0;i<300;i++){    //  
        linea[i]=' ';         
      }       
    }
  }
  return out_trame;
  //out_trame="";
}
