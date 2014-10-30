#include <AccelStepper.h>

// 4 pins of the stepper motor board
#define MOTOR_RIGHT_PIN1 9 //Digital Pin
#define MOTOR_RIGHT_PIN2 10 //Digital Pin
#define MOTOR_RIGHT_PIN3 11 //Digital Pin
#define MOTOR_RIGHT_PIN4 12  //Digital Pin

#define MOTOR_LEFT_PIN1 5 //Digital Pin
#define MOTOR_LEFT_PIN2 6 //Digital Pin
#define MOTOR_LEFT_PIN3 7 //Digital Pin
#define MOTOR_LEFT_PIN4 8 //Digital Pin

#define STEPPER_MODEL_28BYJ_48 (5)

volatile boolean start = true;

AccelStepper RightStepperMotor(STEPPER_MODEL_28BYJ_48, MOTOR_RIGHT_PIN1, MOTOR_RIGHT_PIN2, MOTOR_RIGHT_PIN3, MOTOR_RIGHT_PIN4);
AccelStepper LeftStepperMotor(STEPPER_MODEL_28BYJ_48, MOTOR_LEFT_PIN1, MOTOR_LEFT_PIN2, MOTOR_LEFT_PIN3, MOTOR_LEFT_PIN4);

void setup()
{
  LeftStepperMotor.setMaxSpeed(3.0);
  LeftStepperMotor.setAcceleration(1.0);
  RightStepperMotor.setMaxSpeed(3.0);
  RightStepperMotor.setAcceleration(1.0);
}

void loop()
{
  if (start)
  {
    LeftStepperMotor.moveTo(-50000);
    RightStepperMotor.moveTo(50000);    
    start = false;
  }
  LeftStepperMotor.run();
  RightStepperMotor.run();
}
