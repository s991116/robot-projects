#include <AccelStepper.h>
#define MOTOR1_DIR_PIN (8)
#define MOTOR1_STEP_PIN (9)
// Define the stepper and the pins it will use
AccelStepper stepper1(1, MOTOR1_STEP_PIN, MOTOR1_DIR_PIN);

// Define our maximum and minimum speed in steps per second (scale pot to these)
#define  MAX_SPEED 500
#define  MIN_SPEED 0.1

float current_speed = 200;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // The only AccelStepper value we have to set here is the max speeed, which is higher than we'll ever go 
  stepper1.setMaxSpeed(10000.0);
  stepper1.setSpeed(current_speed);
  Serial.begin(9600);  
  Serial.println("Write speed, and return with newline.");
  inputString.reserve(200);
}

void loop() {
  
  serialEvent(); //call the function
  if(stringComplete)
  {
    current_speed = inputString.toFloat();
    stepper1.setSpeed(current_speed);
    clearString();
  }
  // This will run the stepper at a constant speed
  stepper1.runSpeed();
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void clearString() {
  if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

