#include <PID_v1.h>

PID PIDMotorA(&CurrentEncoderCountA, &MotorPowerA, &TargetEncoderCountA, KpMotorA, KiMotorA, KdMotorA, DIRECT);
PID PIDMotorB(&CurrentEncoderCountB, &MotorPowerB, &TargetEncoderCountB, KpMotorB, KiMotorB, KdMotorB, DIRECT);

void InitializeSpeedControl()
{
  PIDMotorA.SetOutputLimits(-255, 255);
  PIDMotorB.SetOutputLimits(-255, 255);
}

void UpdateMotorPowerBeforeInterrupt()
{
  return;
  unsigned long period = micros() - EncoderInterruptTimeA;
  int power = GetMotorPowerBeforeInterrupt(period);
  SetMotorPowerA(power);  
}

void UpdateMotorPowerAfterInterrupt()
{
  int power = GetMotorPowerAfterInterrupt(InterruptPeriodA);
  SetMotorPowerA(power);
}

void UpdateTargetPeriod(short period)
{
  if(period < 0)
  {
    TargetInterruptForward = false;
    TargetInterruptPeriod = -period;
    MaxMotorPowerA = -255;
  }
  else
  {
    TargetInterruptForward = true;
    TargetInterruptPeriod = period;
    MaxMotorPowerA = 255;
  }
  
  TargetInterruptBrakePeriod = TargetInterruptPeriod / TargetInterruptBrakeFactor;
}

int GetMotorPowerAfterInterrupt(unsigned long interruptPeriod)
{
  if(TargetInterruptPeriod == 0)
  {
    if(ForwardDirectionA)
    {
      return -MaxMotorPowerA;
    }
    else
    {
      return MaxMotorPowerA;    
    }        
  }

  if(TargetInterruptForward != ForwardDirectionA)
  {
    return MaxMotorPowerA;
  }
  
  InterruptPeriodAError = TargetInterruptPeriod - interruptPeriod;// + InterruptPeriodAError;
  
  if(InterruptPeriodAError > 0)
  {
    return MaxMotorPowerA;
  }
  else
  {
    return 0;
  }  
}

int GetMotorPowerBeforeInterrupt(unsigned long period)
{
  if(TargetInterruptPeriod==0)
  {
    return 0;
  }
  
  if(TargetInterruptForward != ForwardDirectionA)
  {
    return MaxMotorPowerA;
  }
    
  if(period < TargetInterruptPeriod)
  {
    return 0;
  }
  else
  {
    return MaxMotorPowerA;
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
  if(NextMotorPowerUpdateTime < t && TargetInterruptPeriod != 0)
  {
    UpdateCurrentEncoderA();
     UpdateMotorPowerBeforeInterrupt();
  }
}

