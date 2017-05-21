#include "DualDriver.h"
#include <Arduino.h>

DualDriver::DualDriver() {
  Initialize(10, 3, 8, 9, 5, 11, 12);
}

DualDriver::DualDriver(int standby_pin, int motorA_pwm_pin, int motorA_in1_pin, int motorA_in2_pin, int motorB_pwm_pin, int motorB_in1_pin, int motorB_in2_pin) {
  Initialize(standby_pin, motorA_pwm_pin, motorA_in1_pin, motorA_in2_pin, motorB_pwm_pin, motorB_in1_pin, motorB_in2_pin);
}

void DualDriver::Initialize(int standby_pin, int motorA_pwm_pin, int motorA_in1_pin, int motorA_in2_pin, int motorB_pwm_pin, int motorB_in1_pin, int motorB_in2_pin) {
  _Standby_pin = standby_pin;
  _MotorA_pwm_pin = motorA_pwm_pin;
  _MotorA_in1_pin = motorA_in1_pin;
  _MotorA_in2_pin = motorA_in2_pin;
  _MotorB_pwm_pin = motorB_pwm_pin;
  _MotorB_in1_pin = motorB_in1_pin;
  _MotorB_in2_pin = motorB_in2_pin;
  
  pinMode(_Standby_pin, OUTPUT);

  pinMode(_MotorA_pwm_pin, OUTPUT);
  pinMode(_MotorA_in1_pin, OUTPUT);
  pinMode(_MotorA_in2_pin, OUTPUT);

  pinMode(_MotorB_pwm_pin, OUTPUT);
  pinMode(_MotorB_in1_pin, OUTPUT);
  pinMode(_MotorB_in2_pin, OUTPUT); 
  
  digitalWrite(_Standby_pin, HIGH); //disable standby
  SetSpeedA(0);
  SetSpeedB(0);
}

void DualDriver::SetSpeedA(int speed) {  
  
  SetSpeed(_MotorA_pwm_pin, _MotorA_in1_pin, _MotorA_in2_pin, speed, true);
}

void DualDriver::SetSpeedB(int speed) {
  SetSpeed(_MotorB_pwm_pin, _MotorB_in1_pin, _MotorB_in2_pin, speed, false);
}

void DualDriver::SetSpeed(int pwm_pin, int in1_pin, int in2_pin, int speed, bool dir_setup)
{
	if(speed > 0)
	{
      digitalWrite(in1_pin, dir_setup);
      digitalWrite(in2_pin, !dir_setup);		
	}
	else
	{
      digitalWrite(in1_pin, !dir_setup);
      digitalWrite(in2_pin, dir_setup);
	  speed = -speed;
	}
	
	speed = LimitSpeed(speed);
    analogWrite(pwm_pin, speed);	
}

int DualDriver::LimitSpeed(int speed) {
	if(speed > 255)
		return 255;
	if(speed < 0)
		return 0;
	return speed;
}