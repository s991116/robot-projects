#include <MotorEncoder.h>
#include <MotorController.h>
#include <PID_v1.h>
#include <MotorPidController.h>

#include "PinsSetup.h"

short updatePeriod = 10;

MotorEncoder motor1Encoder(ENCODER_LEFT_1_PIN, ENCODER_LEFT_2_PIN);
MotorController motor1Controller(MOTOR_1_SPEED_PIN, MOTOR_1_CONTROL_1_PIN, MOTOR_1_CONTROL_2_PIN, false);
MotorPidController motor1PidController(updatePeriod, &motor1Encoder, &motor1Controller, 1.0, 0.0, 0.0, REVERSE);

void setup() {
  Serial.begin(9600);
  motor1PidController.TargetSpeed = 5;
}

void loop() {
  motor1PidController.Compute();
}
