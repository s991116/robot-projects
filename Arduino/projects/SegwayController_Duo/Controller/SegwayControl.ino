#include <PIDFloat.h>
#include <PID_v1.h>

#define NEXTSEGWAYUPDATETIME (5)

unsigned long NextSegwayUpdateTime;
bool SegwayEnabled = false;
short OffsetAngle;

double AnglePCorr = 0.2;
double AngleICorr = 0.1;
double AngleDCorr = 0;
double GyroOutputFactor = 0.01;


double CurrentAngle;
double TargetAngle;
double CorrectionAngle;

double SpeedPCorr = 0.1;
double SpeedICorr = 0;
double SpeedDCorr = 0;

double CurrentSpeed;
double TargetSpeed;
double CorrectionSpeed;

PIDFloat PIDSpeed(&CurrentSpeed, &CorrectionSpeed, &TargetSpeed, SpeedPCorr, SpeedICorr, SpeedDCorr, DIRECT);

PIDFloat PIDGyro(&CurrentAngle, &CorrectionAngle, &TargetAngle, AnglePCorr, AngleICorr, AngleDCorr, DIRECT);
PID PIDMotorA(&CurrentEncoderCountA, &MotorPowerA, &TargetEncoderCountA, KpMotorA, KiMotorA, KdMotorA, REVERSE);
PID PIDMotorB(&CurrentEncoderCountB, &MotorPowerB, &TargetEncoderCountB, KpMotorB, KiMotorB, KdMotorB, DIRECT);

void InitializeSegway()
{
  PIDSpeed.SetOutputLimits(-1000, 1000);  
  PIDGyro.SetOutputLimits(-255/GyroOutputFactor, 255/GyroOutputFactor);
  PIDMotorA.SetOutputLimits(-255, 255);
  PIDMotorB.SetOutputLimits(-255, 255);
}

void SetSegwayEnabled(bool s)
{
  SegwayEnabled = s;

  if(!SegwayEnabled)
  {
    TargetEncoderCountA = 0;
    TargetEncoderCountB = 0;
    serialCommand.sendCommandAndData((uint8_t) 0, (uint8_t) 0);
  }
  else
  {
    serialCommand.sendCommandAndData((uint8_t) 0, (uint8_t) 1);
    delay(1000);
    SetOffsetAngle();    
  }  
}

void SetOffsetAngle()
{
  long averageAngle = 0;
  for(int n=0; n<10; n++)
  {
    long data = GetAngle();
    averageAngle += data;
    delay(50);
  }

  OffsetAngle = (averageAngle / 10.0);
}

bool GetSegwayEnabled()
{
  return SegwayEnabled;
}

void HandleSegway()
{
  long t = millis();
  if(t > NextSegwayUpdateTime)
  {
    NextSegwayUpdateTime = t + NEXTSEGWAYUPDATETIME;
    UpdateSegway();
  }  
}

void UpdateSegway()
{

  UpdateCurrentEncoderA();
  UpdateCurrentEncoderB();

  CurrentSpeed = (CurrentEncoderCountA + CurrentEncoderCountB) / 2;
  PIDSpeed.Compute();

  TargetAngle = 0;// CorrectionSpeed;
   UpdateAngle();
  PIDGyro.Compute();
  
  TargetEncoderCountA = -(CorrectionAngle*GyroOutputFactor);
  TargetEncoderCountB = -(CorrectionAngle*GyroOutputFactor);
  
  PIDMotorA.Compute();
  PIDMotorB.Compute();

  if(SegwayEnabled)
  {
    SetMotorPowerA(MotorPowerA);
    SetMotorPowerB(MotorPowerB);
  }
  else
  {
    SetMotorPowerA(0);
    SetMotorPowerB(0);    
  }
}

void UpdateAngle()
{
  CurrentAngle = (Angle - OffsetAngle)*10;
}

void UpdateGyroPIDSettings()
{  
  PIDGyro.SetTunings(AnglePCorr, AngleICorr, AngleDCorr);
}

void UpdateSpeedPIDSettings()
{  
  PIDGyro.SetTunings(SpeedPCorr, SpeedICorr, SpeedDCorr);
}

void UpdateControllerSettings()
{
  PIDMotorA.SetTunings(KpMotorA, KiMotorA, KdMotorA);
  PIDMotorB.SetTunings(KpMotorB, KiMotorB, KdMotorB);  
}
