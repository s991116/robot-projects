#include "StepperMotor.h"
#include "PinSetup.h"

void StepperMotor::SetLeftMotor(int throttle) {
    this->throttle_left_motor = throttle;
}

void StepperMotor::SetRightMotor(int throttle) {
    this->throttle_right_motor = throttle;
}

void StepperMotor::Update() {
  //Left motor pulse calculations
  this->throttle_counter_left_motor++;                                           //Increase the throttle_counter_left_motor variable by 1 every time this routine is executed
  if(this->throttle_counter_left_motor > this->throttle_left_motor_memory){             //If the number of loops is larger then the throttle_left_motor_memory variable
    this->throttle_counter_left_motor = 0;                                        //Reset the throttle_counter_left_motor variable
    this->throttle_left_motor_memory = this->throttle_left_motor;                       //Load the next throttle_left_motor variable
    if(this->throttle_left_motor_memory < 0){                                     //If the throttle_left_motor_memory is negative                                                 //Set output 3 low to reverse the direction of the stepper controller
      STEPPERMOTOR_LEFT_REVERSE;
      this->throttle_left_motor_memory *= -1;                                     //Invert the throttle_left_motor_memory variable
    }
    else STEPPERMOTOR_LEFT_FORWARD;                                               //Set output 11 high for a forward direction of the stepper motor
  }
  else if(this->throttle_counter_left_motor == 1){
    STEPPERMOTOR_LEFT_HIGH;
  }
  else if(this->throttle_counter_left_motor == 2) {
    STEPPERMOTOR_LEFT_LOW;
  }
  //right motor pulse calculations
  this->throttle_counter_right_motor++;                                          //Increase the throttle_counter_right_motor variable by 1 every time the routine is executed
  if(this->throttle_counter_right_motor > this->throttle_right_motor_memory){           //If the number of loops is larger then the throttle_right_motor_memory variable
    this->throttle_counter_right_motor = 0;                                       //Reset the throttle_counter_right_motor variable
    this->throttle_right_motor_memory = this->throttle_right_motor;                     //Load the next throttle_right_motor variable
    if(this->throttle_right_motor_memory < 0){                                    //If the throttle_right_motor_memory is negative
      STEPPERMOTOR_RIGHT_REVERSE;
      this->throttle_right_motor_memory *= -1;                                    //Invert the throttle_right_motor_memory variable
    }
    else STEPPERMOTOR_RIGHT_FORWARD;
  }
  else if(this->throttle_counter_right_motor == 1){
     STEPPERMOTOR_RIGHT_HIGH;
  }
  else if(this->throttle_counter_right_motor == 2){
     STEPPERMOTOR_RIGHT_LOW;
  }
}