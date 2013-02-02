void setup() {
  Serial.begin(4800);
}

void loop() {
  delay(500);
  String trame = String("#$00$00$")+String(rand()%10)+String(rand()%10)+String("$00$42$@");
  trame += String("#$00$01$")+String(rand()%6)+String(rand()%10)+String("$00$42$@");
  trame += String("#$00$02$")+String(rand()%10)+String(rand()%10)+String("$00$42$@");
  trame += String("#$00$03$")+String(rand()%6)+String(rand()%10)+String("$00$42$@");
  Serial.print(trame);
}  
