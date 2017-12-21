#include <DueMotorEncoder.h>
#include <DueMotorController.h>

#define ENCODER_LEFT_1_PIN (50)
#define ENCODER_LEFT_2_PIN (53)
#define ENCODER_RIGHT_1_PIN (51)
#define ENCODER_RIGHT_2_PIN (52)

#define MOTOR_1_SPEED_PIN (20)
#define MOTOR_1_CONTROL_1_PIN (22)
#define MOTOR_1_CONTROL_2_PIN (24)

#define MOTOR_2_SPEED_PIN (30)
#define MOTOR_2_CONTROL_1_PIN (26)
#define MOTOR_2_CONTROL_2_PIN (28)

short encoderUpdatePeriod = 10;

DueMotorEncoder dueMotorEncoder(ENCODER_LEFT_1_PIN, ENCODER_LEFT_2_PIN, ENCODER_RIGHT_1_PIN, ENCODER_RIGHT_2_PIN, encoderUpdatePeriod);
DueMotorController dueMotor1Controller(MOTOR_1_SPEED_PIN, MOTOR_1_CONTROL_1_PIN, MOTOR_1_CONTROL_2_PIN, true);
DueMotorController dueMotor2Controller(MOTOR_2_SPEED_PIN, MOTOR_2_CONTROL_1_PIN, MOTOR_2_CONTROL_2_PIN, false);

void setup() {
  Serial.begin(9600);
}

void loop() {
//  dueMotorEncoder.Update();
//  Serial.println(dueMotorEncoder.GetSpeedLeft());
  dueMotor1Controller.SetSpeed(255);
  dueMotor2Controller.SetSpeed(255);
  delay(500);
  dueMotor1Controller.SetSpeed(0);
  dueMotor2Controller.SetSpeed(0);
  delay(200);
  dueMotor1Controller.SetSpeed(-255);
  dueMotor2Controller.SetSpeed(-255);
  delay(500);
  dueMotor1Controller.SetSpeed(0);
  dueMotor2Controller.SetSpeed(0);
  delay(200);
}
