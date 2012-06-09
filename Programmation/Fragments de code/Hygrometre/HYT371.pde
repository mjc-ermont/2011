    #include <Wire.h>   // include Wire library for I2C


// initialize the digital pin as an output.
// Pin 13 has an LED connected on most Arduino boards:
#define HYT371_ADDR 0x28
    
void setup() {

    pinMode(13, OUTPUT);
    Wire.begin();   // start Wire library as I2C-Bus Master
    Serial.begin(9600);
}

void loop() {

    double Humidity;
    double Temperature;

    
    Wire.beginTransmission(HYT371_ADDR);
    Wire.send(0);
    Wire.available();
    int Ack = Wire.receive(); // receive a byte

    Wire.endTransmission();
    delay(100);
    
    // READ DATA from here on
    Wire.beginTransmission(HYT371_ADDR);
    Wire.requestFrom(HYT371_ADDR,4);  //Reade 1 byte
    Wire.available();
    int b1 = Wire.receive(); // receive a byte
    int b2 = Wire.receive(); // receive a byte
    int b3 = Wire.receive(); // receive a byte
    int b4 = Wire.receive(); // receive a byte
    Wire.send(0); //NACK

    // combine the bits
    int RawHumidBin = b1 << 8 | b2;
    // compound bitwise to get 14 bit measurement first two bits
    // are status/stall bit (see intro text)
    RawHumidBin =  (RawHumidBin &= 0x3FFF);
    Humidity = 100.0/pow(2,14)*RawHumidBin;

    b4 = (b4 &= 0x3F); //Mask away 2 least sign. bits see HYT 221 doc
    int RawTempBin = b3 << 6 | b4;
    Temperature = 165.0/pow(2,14)*RawTempBin-40;

    Wire.endTransmission();

    digitalWrite(13, HIGH);   // set the LED on
    delay(250);              // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(250);              // wait for a second

    Serial.print("H=");
    Serial.print(Humidity);
    Serial.print("T=");
    Serial.print(Temperature);
    Serial.print("C=");
    Serial.print(analogRead(0));
    Serial.print("F");
 }
