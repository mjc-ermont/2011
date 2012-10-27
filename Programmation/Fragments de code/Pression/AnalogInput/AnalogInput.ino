void setup() {
  
  Serial.begin(9600); 
}
 
void loop() {
   int sensorValue;
   
   sensorValue = analogRead(5);  
   float volt = ((float)sensorValue*5)/1023;
   Serial.println(volt);  
   
   float pr = ((volt-0.2)/(0.045));
   
   //int alt = -99.01*pow(sensorValue,5) + 1135*pow(sensorValue,4) - 4843.2*pow(sensorValue,3) + 9980.9*pow(sensorValue,2) - 13661*sensorValue + 15781;
   
   Serial.println(pr);
   //Serial.println(alt);  
  
   delay(500);
}
