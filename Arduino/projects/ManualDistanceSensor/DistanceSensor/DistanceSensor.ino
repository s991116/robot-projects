#include <NewPing.h>

/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define TRIGGER_PIN  4
#define ECHO_PIN     3
#define MAX_DISTANCE_IN_CM 10 
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_IN_CM);

void setup() {
  Serial.begin (9600);
}

void loop() {
  long distance = ultrasonic.ping_cm();
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
