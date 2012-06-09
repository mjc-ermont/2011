#include "gps.h"
#include "trame.h"

GPS::GPS(){

}

bool GPS::init(){

}

bool GPS::refresh(){
  char current_char = 0;
  char *trame_char;
  String trame = "", table[20];
  char *str;      
  
  trame_char = (char*)malloc(100 * sizeof(char));
  
  if (Serial1.available() > 0){
    while (Serial1.read() != '$');
    
    while (true){
      current_char = Serial1.read();
      if (current_char == '*'){
        break;
      }
      if (current_char != -1){
        trame += current_char;
      }
    }
    Serial.println(trame);
    trame.toCharArray(trame_char, 100);

    int i = 0;
    while ((table[i] = strsep(&trame_char, ",")) != NULL)      
      i++;
      
    for (int j = 0 ; j < sizeof(table) ; j++){
      Serial.println(table[j]);
    }
    free(str);
    free(trame_char);
    trame = "";
    
    return true;
  } else {
    return false;
  }
}
