#include "Wire.h"

#define LED_PIN (13)
#define MPU6050_ADDRESS (0x68)

boolean blinkState;

void setup() {
    Wire.begin();
    
    Serial.begin(38400);
    // initialize device
    Serial.println("Initializing I2C devices...");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
  blinkLED();
  long startTime = millis();
  for(int i=0;i<1000;i++)
  {
    int angle = ReadAngle();
  }
  long endTime = millis();
  long duration = endTime - startTime;
  PrintNumber(duration);
}

void SendData(byte reg, byte data) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(reg);  // PWR_MGMT_1 register
  Wire.write(data);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void InitializeGyro() {
  SendData(0x6B, 0);
  
  delayMicroseconds(5);
  SendData(0x6b, 0x03); // set z axis as clock source
  SendData(0x1a, 0x00); // disables FSYNC, configures DPLF
  SendData(0x1b, 0x18);   //0b11000 set range to 2000*2
	      
  delayMicroseconds(100);
  SendData(0x6b, 0x00); // reset all register to default
}

int ReadAngle() {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(0x43);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDRESS,2,true);  // request a total of 2 registers
  int X=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
 return X;
}

void PrintNumber(int number)
{
  Serial.print("Number: ");
  Serial.print(number);
  Serial.print("\n");
}

void blinkLED() {
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
