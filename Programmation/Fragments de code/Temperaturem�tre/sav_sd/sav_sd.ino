#include <SD.h>
#include <math.h>

const int chipSelect = 4;
 double timeElapsed = 0;

double readTemp(int RawADC) {
 double Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 return Temp;
}

void setup() {
 Serial.begin(115200);
 Serial.print("Initializing SD card...");
 // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("Card initialized.");
  
  File dataFile = SD.open("temp.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Temperature");
    dataFile.close();
  }
  
  
}

void loop() {
  
  timeElapsed += 0.5;
  
  double temp = readTemp(analogRead(0));
  
  String dataString = "[";
  dataString += dtostrf(timeElapsed, 1, 1, "dddddd.d");
  dataString += "]";
  dataString += dtostrf(temp, 1, 2, "dd.dd");
  
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("temp.txt", FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("Error opening datalog.txt");
  } 
    Serial.println(dataString);
  
  delay(500);
}

