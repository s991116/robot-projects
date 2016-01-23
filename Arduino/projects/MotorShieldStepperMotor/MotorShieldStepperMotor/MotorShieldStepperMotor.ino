#include <Stepper.h>

const int stepsPerRevolution = 240;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library using the default pins on the HBridge Shield:
Stepper myStepper(stepsPerRevolution, 5, 4, 6, 7);

void setup() {
  // set the speed at 200 rpm:
  myStepper.setSpeed(200);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
   Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);
  
   // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000); 
}
