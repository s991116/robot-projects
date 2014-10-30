/*
  Distance sensor test.
  Ultrasonic -> Arduino
    TRIG -> PIN 12
    ECHO -> PIN 11
  
  LED -> Arduino
    LED -> PIN 13
  
  Blink speed is propertional to measured distance.
  
*/
#include <Ultrasonic.h>

  Ultrasonic ultrasonic(12,11);
  int led = 13;

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
}

void loop()
{
  long t = ultrasonic.Ranging(CM);
  delay(25*t);
  digitalWrite(led, HIGH);    
  t = ultrasonic.Ranging(CM);
  delay(25*t);
  digitalWrite(led, LOW);
}




