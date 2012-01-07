void setup (){
  
  int rxbyte = 0;
  
  Serial.begin(9600);
  Serial1.begin(9600);
  
  Serial.println("Debut du programme");
  Serial1.print(0x10);
  Serial.println("Byte DLE envoyé");
  
  Serial1.print(0x42);  
  Serial.println("Byte id Envoyé");
  
  Serial1.print(0xBC);
  Serial.println("Byte de selection de protocole envoyé");
  
  Serial1.print(0x01);
  Serial.println("Byte de selsction du port envoyé");
  
  Serial1.print(0x07);
  Serial.println("Byte de selection du debit entrant envoyé");
  
  Serial1.print(0x07);
  Serial.println("Byte de selection du debit sortant envoyé");
  
  Serial1.print(0x03);
  Serial.println("Byte de selection du nombre de bits de données envoyé");
  
  Serial1.print(0x01);
  Serial.println("Byte de selection du type de parité envoyé");
  
  Serial.print(0x00);
  Serial.println("Byte de selection du nombre de bits de stop envoyé");
  
  Serial1.print(0x00);
  Serial.println("Byte de selection du \"flow control\" envoyé");
  
  Serial.print(0b01000000);
  Serial.println("Byte de selection du protocole d'entrée envoyé");
  
  Serial.print(0b01000000);
  Serial.println("Byte de selection du protocole d'entrée envoyé");
  
  Serial.print(0x00);
  Serial.println("Byte qui sert a rien envoyé");
  
  Serial1.print(0x10);
  Serial.println("Byte DLE envoyé");
  
  Serial1.print(0x03);
  Serial.println("Byte ETX envoyé");
  
  while (rxbyte = Serial1.read() != -1){
    Serial.print(rxbyte);
  }
}  

void loop (){
  
  char rxbyte = 0;
  
  Serial.println("Requete TAIP");
  
  Serial1.print(">QPV<");
  
  while (rxbyte = Serial1.read() /*!= -1*/){
    
    /*if (rxbyte == 'R'){
      Serial.println("OK 1");
    }
    if (rxbyte == 'P'){
      Serial.println("OK 2");
    }
    if (rxbyte == 'V'){
      Serial.println("OK 3");
    }*/
    
    if (rxbyte == -1){
      break;
    } 
    
    Serial.print(rxbyte);
    
  }
  
}
