#include <PID_v1.h>

PID PIDMotorA(&CurrentEncoderCountA, &MotorPowerA, &TargetEncoderCountA, KpMotorA, KiMotorA, KdMotorA, DIRECT);
PID PIDMotorB(&CurrentEncoderCountB, &MotorPowerB, &TargetEncoderCountB, KpMotorB, KiMotorB, KdMotorB, DIRECT);

void InitializeSpeedControl()
{
  PIDMotorA.SetOutputLimits(-255, 255);
  PIDMotorB.SetOutputLimits(-255, 255);
}

void UpdateMotorPower()
{
  if(MotorPowerUpdateTime())
  {
    UpdateCurrentEncoderA();
    PIDMotorA.Compute();
    SetMotorPowerA(MotorPowerA);
    UpdateCurrentEncoderB();
    PIDMotorB.Compute();
    SetMotorPowerB(MotorPowerB);
  }
}

void UpdateControllerSettings()
{
  PIDMotorA.SetTunings(KpMotorA, KiMotorA, KdMotorA);
  PIDMotorB.SetTunings(KpMotorB, KiMotorB, KdMotorB);  
}

bool MotorPowerUpdateTime()
{
  long t = millis();
  if(NextMotorPowerUpdateTime < t)
  {
     NextMotorPowerUpdateTime = t + MotorPowerUpdatePeriod;
     return true;
  }
  return false;
}

