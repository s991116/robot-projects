#include <PID_v1.h>
/*
PID PIDMotorA(&CurrentEncoderCountA, &MotorPowerA, &TargetEncoderCountA, KpMotorA, KiMotorA, KdMotorA, DIRECT);
PID PIDMotorB(&CurrentEncoderCountB, &MotorPowerB, &TargetEncoderCountB, KpMotorB, KiMotorB, KdMotorB, REVERSE);

void InitializeSpeedControl()
{
  PIDMotorA.SetOutputLimits(-255, 255);
  PIDMotorB.SetOutputLimits(-255, 255);
}

void UpdateMotorPower()
{
  //UpdateCurrentEncoderA();
  //UpdateCurrentEncoderB();
  PIDMotorA.Compute();
  PIDMotorB.Compute();
  SetMotorPowerA(MotorPowerA);
  SetMotorPowerB(MotorPowerB);
}

void UpdateControllerSettings()
{
  PIDMotorA.SetTunings(KpMotorA, KiMotorA, KdMotorA);
  PIDMotorB.SetTunings(KpMotorB, KiMotorB, KdMotorB);  
}

void MotorPowerUpdateTime()
{
  long t = millis();
  if(t > NextMotorPowerUpdateTime)
  {
    NextMotorPowerUpdateTime = t + MotorUpdatePeriod;
    UpdateMotorPower();
  }
}

*/
