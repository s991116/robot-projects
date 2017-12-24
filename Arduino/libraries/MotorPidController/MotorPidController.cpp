#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MotorPidController.h>

MotorPidController::MotorPidController(short updatePeriod, MotorEncoder *encoder, MotorController *motorController, double p, double i, double d, int direction) {
    _updatePeriod = updatePeriod;
    _encoder = encoder;
    _motorController = motorController;
    MotorPID = new PID(&_PIDInput, &_PIDOutput, &TargetSpeed, p, i, d, direction);
    MotorPID->SetOutputLimits(-255.0, 255.0);
}

void MotorPidController::Update() {
  if(millis() > _nextUpdateTime) {
    _encoder->Compute();
    _PIDInput = _encoder->GetSpeed();
    MotorPID->Compute();
    _motorController->SetSpeed(_PIDOutput);
    _nextUpdateTime += _updatePeriod;
  }
}