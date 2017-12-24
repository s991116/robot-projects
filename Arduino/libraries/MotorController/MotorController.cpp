#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MotorController.h>

MotorController::MotorController(short speedPin, short controlPin1, short controlPin2, bool direction) {
  _SpeedPin = speedPin;
  _ControlPin1 = controlPin1;
  _ControlPin2 = controlPin2;
  _Direction = direction;

  pinMode(_SpeedPin, OUTPUT);
  pinMode(_ControlPin1, OUTPUT);
  pinMode(_ControlPin2, OUTPUT);
}

void MotorController::SetSpeed(short speed) {
  _Speed = speed;
  if(_Speed > 0) {
    digitalWrite(_ControlPin1, _Direction);
    digitalWrite(_ControlPin2, !_Direction);
    analogWrite(_SpeedPin, _Speed);
  }
  else if(_Speed < 0) {
    digitalWrite(_ControlPin1, !_Direction);
    digitalWrite(_ControlPin2, _Direction);
    analogWrite(_SpeedPin, -_Speed);
  }
  else {
    digitalWrite(_ControlPin1, LOW);
    digitalWrite(_ControlPin2, LOW);
    analogWrite(_SpeedPin, 0);
  }
}

short MotorController::GetSpeed() {
    return _Speed;
}