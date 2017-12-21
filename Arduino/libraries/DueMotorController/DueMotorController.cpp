#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <DueMotorController.h>

DueMotorController::DueMotorController(short speedPin, short control1Pin, short control2Pin, bool direction) {
  DueMotorController::_SpeedPin = speedPin;
  DueMotorController::_Control1Pin = control1Pin;
  DueMotorController::_Control2Pin = control2Pin;
  DueMotorController::_Direction = direction;

  pinMode(DueMotorController::_SpeedPin, OUTPUT);
  pinMode(DueMotorController::_Control1Pin, OUTPUT);
  pinMode(DueMotorController::_Control2Pin, OUTPUT);
}

void DueMotorController::SetSpeed(short speed) {
  DueMotorController::_Speed = speed;
  if(DueMotorController::_Speed > 0) {
    digitalWrite(DueMotorController::_Control1Pin, DueMotorController::_Direction);
    digitalWrite(DueMotorController::_Control2Pin, !DueMotorController::_Direction);
    analogWrite(DueMotorController::_SpeedPin, DueMotorController::_Speed);
  }
  else if(DueMotorController::_Speed < 0) {
    digitalWrite(DueMotorController::_Control1Pin, !DueMotorController::_Direction);
    digitalWrite(DueMotorController::_Control2Pin, DueMotorController::_Direction);
    analogWrite(DueMotorController::_SpeedPin, -DueMotorController::_Speed);
  }
  else {
    digitalWrite(DueMotorController::_Control1Pin, LOW);
    digitalWrite(DueMotorController::_Control2Pin, LOW);
    analogWrite(DueMotorController::_SpeedPin, 0);
  }
}

short DueMotorController::GetSpeed() {
    return DueMotorController::_Speed;
}