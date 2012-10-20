void setup() {
  Serial.begin(9600); 
}
 
void loop() {
  int sensorValue = analogRead(15);
    Serial.println(sensorValue);                                                        
  float volt = ((float)sensorValue*5)/1023;
  
  float pr = ((volt)/(0.045))-0.2;
  
  int alt = -99.01*pow(sensorValue,5) + 1135*pow(sensorValue,4) - 4843.2*pow(sensorValue,3) + 9980.9*pow(sensorValue,2) - 13661*sensorValue + 15781;
  
  Serial.println(pr);
  //Serial.println(alt);  
  
  delay(500);
}
