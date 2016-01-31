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
  unsigned long interruptPeriod = micros() - EncoderInterruptTimeA;
  UpdateMotorPower(interruptPeriod);
}

void UpdateMotorPower(unsigned long timer)
{
  
  byte power = GetMotorPower(timer);
  SetMotorPowerA(power);  
}

byte GetMotorPower(unsigned long interruptPeriod)
{
  if(TargetInterruptPeriod == 0)
  {    
    return 0;
  }
  
  if(interruptPeriod > TargetInterruptPeriod)
  {
    return 255;
  }
  else
  {
    return 0;    
  }  
}

void UpdateControllerSettings()
{
  PIDMotorA.SetTunings(KpMotorA, KiMotorA, KdMotorA);
  PIDMotorB.SetTunings(KpMotorB, KiMotorB, KdMotorB);  
}

void MotorPowerUpdateTime()
{
  long t = millis();
  if(NextMotorPowerUpdateTime < t)
  {
     UpdateMotorPower();
  }
}

