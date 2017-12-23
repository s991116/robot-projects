#include <DueMotorEncoder.h>
#include <DueMotorController.h>
#include <PID_v1.h>

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

short updatePeriod = 10;
unsigned long nextUpdateTime;

int motor1PIDSetpoint, motor1PIDInput, motor1PIDOutput;
PID motor1PID(&motor1PIDInput, &motor1PIDOutput, &motor1PIDSetpoint, 0.0, 0.0, 0.0, REVERSE);

DueMotorEncoder dueMotor1Encoder(ENCODER_LEFT_1_PIN, ENCODER_LEFT_2_PIN);

DueMotorController dueMotor1Controller(MOTOR_1_SPEED_PIN, MOTOR_1_CONTROL_1_PIN, MOTOR_1_CONTROL_2_PIN, false);
DueMotorController dueMotor2Controller(MOTOR_2_SPEED_PIN, MOTOR_2_CONTROL_1_PIN, MOTOR_2_CONTROL_2_PIN, true);

void setup() {
  Serial.begin(9600);
  motor1PID.SetOutputLimits(-255.0, 255.0);

  motor1PIDSetpoint = 5;
}

void loop() {
  if(millis() > nextUpdateTime) {
    dueMotor1Encoder.Compute();
    motor1PIDInput = dueMotor1Encoder.GetSpeed();
    motor1PID.Compute();
    dueMotor1Controller.SetSpeed(motor1PIDOutput);

    nextUpdateTime += updatePeriod;
  }
}
