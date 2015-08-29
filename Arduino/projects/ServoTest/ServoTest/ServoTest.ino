#include <Servo.h> 
 
Servo servo1;
Servo servo2;

#define SERVO_1_PIN (10)
#define SERVO_2_PIN (11)
 
int position1 = 90;
int position2 = 90;

void setup() 
{ 
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  servo1.write(position1);
  servo2.write(position2);
}

short minPosition = 50;
short maxPosition = 130;

void loop() {
}

