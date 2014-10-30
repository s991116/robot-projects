#include <SoftI2CMaster.h>

#define SDA_PIN (5)
#define SCL_PIN (6)
#define GYRO_ADDRESS (0x68) //0x68 or 0xD0
#define WHO_AM_I (0x75)
#define PIN_LED (13)

void setup()
{  
  Serial.begin(9600);
  Serial.println("Ready.");
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  ReadFromGyro();
}

void ReadFromGyro()
{
  SoftI2CMaster i2c = SoftI2CMaster( SDA_PIN, SCL_PIN );
  
  i2c.beginTransmission(GYRO_ADDRESS);    // Get the slave's attention, tell it we're sending a command byte
  i2c.send((byte) WHO_AM_I);                   //  The command byte, sets pointer to register with address of 0x32
  i2c.endTransmission();

  i2c.requestFrom(GYRO_ADDRESS);          // Tell slave we need to read 1byte from the current register
  byte slaveByte = i2c.receive();

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
