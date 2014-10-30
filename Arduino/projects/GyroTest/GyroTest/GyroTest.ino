#include <Wire.h>

#define GYRO_ADDRESS (0x68)
#define EV3_ADDRESS (0x11)
#define WHO_AM_I (0x75)
#define PIN_LED (13)

void setup()
{
  Wire.begin(EV3_ADDRESS);
  Serial.begin(9600);
  Serial.println("Ready.");
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int nrOfBytes)
{
  digitalWrite(PIN_LED, HIGH);

  delay(100);
  Wire.read();  
  Wire.read();  
  delay(100);

  digitalWrite(PIN_LED, LOW);

  ReadFromGyro();
}

void ReadFromGyro()
{
  
  Wire.beginTransmission(GYRO_ADDRESS);    // Get the slave's attention, tell it we're sending a command byte
  Wire.write((byte) WHO_AM_I);                   //  The command byte, sets pointer to register with address of 0x32

  Wire.endTransmission();

  Wire.requestFrom(GYRO_ADDRESS,1);          // Tell slave we need to read 1byte from the current register
  byte slaveByte = Wire.read();


  Serial.println(slaveByte);  
  if(slaveByte == 104)
  {
    digitalWrite(PIN_LED, HIGH);
  }
}

void loop() 
{
  delay(10); 
}
