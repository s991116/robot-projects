#include <Wire.h>

#define GYRO_ADDRESS (0x68)
#define PIN_LED (13)
void setup()
{
  Wire.begin(GYRO_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop()
{
  delay(100);
}

void requestEvent()
{
  digitalWrite(PIN_LED, HIGH);
  char data = Wire.read(); // receive byte as a character
  Wire.write(data);
}
