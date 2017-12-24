#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MotorController.h>

MotorController::MotorController(short speedPin, short control1Pin, short control2Pin, bool direction) {
  MotorController::_SpeedPin = speedPin;
  MotorController::_Control1Pin = control1Pin;
  MotorController::_Control2Pin = control2Pin;
  MotorController::_Direction = direction;

  pinMode(MotorController::_SpeedPin, OUTPUT);
  pinMode(MotorController::_Control1Pin, OUTPUT);
  pinMode(MotorController::_Control2Pin, OUTPUT);
}

void MotorController::SetSpeed(short speed) {
  MotorController::_Speed = speed;
  if(MotorController::_Speed > 0) {
    digitalWrite(MotorController::_Control1Pin, MotorController::_Direction);
    digitalWrite(MotorController::_Control2Pin, !MotorController::_Direction);
    analogWrite(MotorController::_SpeedPin, MotorController::_Speed);
  }
  else if(MotorController::_Speed < 0) {
    digitalWrite(MotorController::_Control1Pin, !MotorController::_Direction);
    digitalWrite(MotorController::_Control2Pin, MotorController::_Direction);
    analogWrite(MotorController::_SpeedPin, -MotorController::_Speed);
  }
  else {
    digitalWrite(MotorController::_Control1Pin, LOW);
    digitalWrite(MotorController::_Control2Pin, LOW);
    analogWrite(MotorController::_SpeedPin, 0);
  }
}

short MotorController::GetSpeed() {
    return MotorController::_Speed;
}