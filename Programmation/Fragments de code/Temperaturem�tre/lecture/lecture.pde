#include <math.h>

double Thermister(int RawADC) {
 double Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 return Temp;
}

void setup() {
 Serial.begin(115200);
}

void loop() {
 Serial.println(Thermister(analogRead(0)));  // display Fahrenheit
 delay(100);
}

