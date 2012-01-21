void setup (){
  
  int rxbyte = 0;
  int trame[15];
  
  Serial.begin(9600);
  Serial1.begin(9600);
  
  Serial.println("Debut du programme");
  
  trame[0] = 0x10;
  Serial.println("Byte DLE envoyé");
  
  trame[1] = 0x00;  
  Serial.println("Byte id Envoyé");
  
  trame[2] = 0xBC;
  Serial.println("Byte de selection de protocole envoyé");
  
  trame[3] = 0x01;
  Serial.println("Byte de selection du port envoyé");
  
  trame[4] = 0x07;
  Serial.println("Byte de selection du debit entrant envoyé");
  
  trame[5] = 0x07;
  Serial.println("Byte de selection du debit sortant envoyé");
  
  trame[6] = 0x03;
  Serial.println("Byte de selection du nombre de bits de données envoyé");
  
  trame[7] = 0x01;
  Serial.println("Byte de selection du type de parité envoyé");
  
  trame[8] = 0x00;
  Serial.println("Byte de selection du nombre de bits de stop envoyé");
  
  trame[9] = 0x00;
  Serial.println("Byte de selection du \"flow control\" envoyé");
  
  trame[10] = 0x40;
  Serial.println("Byte de selection du protocole d'entrée envoyé");
  
  trame[11] = 0x40;
  Serial.println("Byte de selection du protocole d'entrée envoyé");
  
  trame[12] = 0x00;
  Serial.println("Byte qui sert a rien envoyé");
  
  trame[13] = 0x10;
  Serial.println("Byte DLE envoyé");
  
  trame[14] = 0x03;
  Serial.println("Byte ETX envoyé");
  
  Serial1.write((uint8_t*)trame, (size_t)15);
  
  while ((rxbyte = Serial1.read()) != -1){
    Serial.print(" 0x");
    Serial.print(rxbyte, HEX);
  }
}  

void loop (){
  
  char rxbyte = 0;
  
  Serial.println("Requete TAIP PV");
  
  Serial1.print(">QVR<");
  Serial.print("Reponse : ");
  
  while ((rxbyte = Serial1.read()) != -1){    
    Serial1.print(rxbyte);    
  }
  
  Serial.println("");
  
}
