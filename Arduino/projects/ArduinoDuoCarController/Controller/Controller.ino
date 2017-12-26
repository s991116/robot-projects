#include <MotorEncoder.h>
#include <MotorController.h>
#include <PID_v1.h>
#include <MotorPidController.h>
#include <Messenger.h>
#include "PinsSetup.h"

short updatePeriod = 10;
double PID_p = 2.0;
double PID_i = 2.0;
double PID_d = 0.0;

MotorEncoder motorLeftEncoder(ENCODER_LEFT_PIN_1, ENCODER_LEFT_PIN_2, false);
MotorController motorLeftController(MOTOR_LEFT_SPEED_PIN, MOTOR_LEFT_CONTROL_PIN_1, MOTOR_LEFT_CONTROL_PIN_2, false);
MotorPidController motorLeftPidController(updatePeriod, &motorLeftEncoder, &motorLeftController, PID_p, PID_i, PID_d, REVERSE);

void motorLeftEncoderInterrupt() {
  motorLeftEncoder.EncoderInterrupt();
}

MotorEncoder motorRightEncoder(ENCODER_RIGHT_PIN_1, ENCODER_RIGHT_PIN_2, false);
MotorController motorRightController(MOTOR_RIGHT_SPEED_PIN, MOTOR_RIGHT_CONTROL_PIN_1, MOTOR_RIGHT_CONTROL_PIN_2, true);
MotorPidController motorRightPidController(updatePeriod, &motorRightEncoder, &motorRightController, PID_p, PID_i, PID_d, REVERSE);

void motorRightEncoderInterrupt() {
  motorRightEncoder.EncoderInterrupt();
}


Messenger message = Messenger(','); 

void messageReady() {
       int targetSpeed;
       double p,i,d;
       while ( message.available() ) {
         switch(message.readChar()) {
           case 's':
             targetSpeed = message.readInt();
     	       motorLeftPidController.TargetSpeed = targetSpeed;
     	       motorRightPidController.TargetSpeed = targetSpeed; 
             break;
           case 'p':
             p = message.readInt()/10.0;
             i = message.readInt()/10.0;
             d = message.readInt()/10.0;
             motorLeftPidController.MotorPID->SetTunings(p, i, d);
             motorRightPidController.MotorPID->SetTunings(p, i, d);
             break;
         }
      }
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(ENCODER_LEFT_PIN_1, motorLeftEncoderInterrupt, CHANGE);
  attachInterrupt(ENCODER_RIGHT_PIN_1, motorRightEncoderInterrupt, CHANGE);

  message.attach(messageReady);
  motorLeftPidController.TargetSpeed = 0.0;
  motorRightPidController.TargetSpeed = 0.0;
}

unsigned long serialUpdateTime;
short serialUpdatePeriod = 100;

void loop()
{
  motorLeftPidController.Update();
  motorRightPidController.Update();
  if(millis() > serialUpdateTime)
  {
    Serial.print(motorRightEncoder.GetSpeed());
    Serial.print(" , ");
    Serial.println(motorRightController.GetSpeed());
    serialUpdateTime += serialUpdatePeriod;
    while ( Serial.available() ) {
      message.process(Serial.read());
    } 
  }
}
