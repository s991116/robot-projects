#include <MotorEncoder.h>
#include <MotorController.h>
#include <PID_v1.h>
#include <MotorPidController.h>

#include "PinsSetup.h"

short updatePeriod = 10;
double PID_p = 1.0;
double PID_i = 0.0;
double PID_d = 0.0;

MotorEncoder motorLeftEncoder(ENCODER_LEFT_PIN_1, ENCODER_LEFT_PIN_2);
MotorController motorLeftController(MOTOR_LEFT_SPEED_PIN, MOTOR_LEFT_CONTROL_PIN_1, MOTOR_LEFT_CONTROL_PIN_2, false);
MotorPidController motorLeftPidController(updatePeriod, &motorLeftEncoder, &motorLeftController, PID_p, PID_i, PID_d, REVERSE);

void motorLeftEncoderInterrupt() {
  motorLeftEncoder.EncoderInterrupt();
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(ENCODER_LEFT_PIN_1, motorLeftEncoderInterrupt, CHANGE);

  motorLeftPidController.TargetSpeed = 5;
}

void loop()
{
  motorLeftPidController.Update();
}
