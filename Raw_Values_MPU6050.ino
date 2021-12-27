// by - GURJOT 27/12/2021 1:31 AM

#include <Wire.h>
//define saves space on board and serves as a reference before compliling..
#define sensed_tempD_0 0x42
#define sensed_tempD_1 0x41 
//Module MPU6050's address on I2C comm.
byte MPU_Addr = 0x68;
//Accel Registers Addrs
byte XaccelD_1 = 0x3B;
byte XaccelD_0 = 0x3C;
byte YaccelD_1 = 0x3D;
byte YaccelD_0 = 0x3E;
byte ZaccelD_1 = 0x3F;
byte ZaccelD_0 = 0x40;
//Gyro Registers Addrs
byte XgyroD_1 = 0x43;
byte XgyroD_0 = 0x44;
byte YgyroD_1 = 0x45;
byte YgyroD_0 = 0x46;
byte ZgyroD_1 = 0x47;
byte ZgyroD_0 = 0x48;
//ignore all these register adresses, only the first one matters, as they are in series...
//Raw Values
float X_ac, Y_ac, Z_ac;
float X_av, Y_av, Z_av;
float temp;
//setup code start
void setup() {
  Serial.begin(9600); //initiates serial monitor at baud 9600
  Wire.begin();
  Wire.beginTransmission(MPU_Addr);
  Wire.write(0x6B); //points to pwr_mngnt 1 register to wake up the board
  Wire.write(0); //wakes up the board
  Wire.endTransmission(true);
  delay(10);
   
   }

void loop() {
  Wire.beginTransmission(MPU_Addr);
  Wire.write(XaccelD_0); //Start with lowest register
  Wire.endTransmission(false); // Why False? keep the bus active after transmission
  Wire.requestFrom(XaccelD_0, 14, true); //true bcoz we're ending transmission here
  //as all the sensor registors are in series just read them all at once.
  X_ac = Wire.read() << 8 | Wire.read();
  Y_ac = Wire.read() << 8 | Wire.read();
  Z_ac = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read();
  X_av = Wire.read() << 8 | Wire.read();
  Y_av = Wire.read() << 8 | Wire.read();
  Z_av = Wire.read() << 8 | Wire.read();
  //converting raw into g values,gauss and celsius
  X_ac = X_ac / 16384 ;
  Y_ac = Y_ac / 16384 ;
  Z_ac = Z_ac / 16384 ;
  temp = (temp / 340) + 36.53 ;
  X_av = X_av / 131 ;
  Y_av = Y_av / 131 ;
  Z_av = Z_av / 131 ;
  
  //raw data is stored in variables
  // print at serial monitor in order
  Serial.print("aX = "); Serial.print(X_ac);
  Serial.print("aY = "); Serial.print(Y_ac);
  Serial.print("aZ = "); Serial.print(Z_ac);
  Serial.print("gX = "); Serial.print(X_av);
  Serial.print("gY = ");Serial.print(Y_av); 
  Serial.print("gZ = "); Serial.print(Z_av);
  Serial.print("T = "); Serial.print(temp);

  //optional delay for raw data monitoring
  delay(1000);



}
