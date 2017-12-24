#ifndef MotorPidController_H
#define MotorPidController_H

#include <PID_v1.h>
#include <MotorEncoder.h>
#include <MotorController.h>

class MotorPidController {
    public:
      MotorPidController(short updatePeriod, MotorEncoder *encoder, MotorController *motorController, double p, double i, double d, int direction);
    
      void Compute();

      PID* MotorPID;
      int TargetSpeed;

    private:
      volatile int _PIDInput;
      int _PIDOutput;
      
      
      MotorEncoder* _encoder;
      MotorController* _motorController;

      short _updatePeriod;
      unsigned long _nextUpdateTime;
};

#endif