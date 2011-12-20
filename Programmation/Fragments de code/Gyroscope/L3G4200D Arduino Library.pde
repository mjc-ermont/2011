#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 104; //I2C address of the L3G4200D on the pad "0"

long x, moy_x = 0;
long y, moy_y = 0;
long z, moy_z = 0;
long init_x = 0;
long init_y = 0;
long init_z = 0;
int count;

void setup(){

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  Wire.begin();
  Serial.begin(9600);

  Serial.println("starting up L3G4200D");
  setupL3G4200D(2000); // Configure L3G4200  - 250, 500 or 2000 deg/sec

  delay(1500); //wait for the sensor to be ready 
 
  moy_x = 0;
  moy_y = 0;
  moy_z = 0;
  
  for (count= 0; count < 100; count++)
  {
    getGyroValues();  // This will update x, y, and z with new values
    moy_x += x;
    moy_y += y;
    moy_z += z;
    
    delay(10);
  }
  
  moy_x /= 100;
  moy_y /= 100;
  moy_z /= 100;
    
  init_x = moy_x;
  init_y = moy_y;
  init_z = moy_z;
  
  Serial.print("init_X: ");
  Serial.print(init_x);

  Serial.print("    init_Y: ");
  Serial.print(init_y);

  Serial.print("    init_Z: ");
  Serial.println(init_z);
}

void loop()
{
  
  moy_x = 0;
  moy_y = 0;
  moy_z = 0;
  
  for (count= 0; count < 10; count++)
  {
    getGyroValues();  // This will update x, y, and z with new values
    moy_x += x;
    moy_y += y;
    moy_z += z;
    
    delay(10);
  }

  moy_x /= 10;
  moy_y /= 10;
  moy_z /= 10;
  
  x -= init_x;
  y -= init_y;
  z -= init_z;
  
  x += 100;
  y += 100;
  z += 100;
  
  Serial.print("X: ");
  Serial.print(x);

  Serial.print("      Y: ");
  Serial.print(y);

  Serial.print("      Z: ");
  Serial.println(z);

  //delay(100); //Just here to slow down the serial to make it more readable
}

void getGyroValues(){

  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  x = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  y = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  z = ((zMSB << 8) | zLSB);
}

int setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.send(address);       // send register address
    Wire.send(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.send(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
        // waiting
    }

    v = Wire.receive();
    return v;
}