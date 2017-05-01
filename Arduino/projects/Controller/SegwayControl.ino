#include <PIDFloat.h>
#include <PID_v1.h>

#define GyroOutputFactor (0.01)

double CorrectionAngle;

double CurrentSpeed;
double CorrectionSpeed;

#define CurrentSpeedBufferSize 5
double CurrentSpeedBuffer[CurrentSpeedBufferSize];
int CurrenSpeedBufferIndex = 0;
double CurrentSpeedBufferAverage = 0;
double SpeedScale = 4;

PIDFloat PIDSpeed(&CurrentSpeed, &CorrectionSpeed, &TargetSpeed, SpeedPCorr, SpeedICorr, SpeedDCorr, DIRECT);
PIDFloat PIDGyro(&CurrentAngle, &CorrectionAngle, &TargetAngle, AnglePCorr, AngleICorr, AngleDCorr, REVERSE);

void SetupSegwayController()
{
  PIDSpeed.SetOutputLimits(-SpeedPIDLimit, SpeedPIDLimit);  
  PIDGyro.SetOutputLimits(-255/GyroOutputFactor, 255/GyroOutputFactor);
}

void SetSegwayEnabled(bool s)
{
  SegwayEnabled = s;

  if(!SegwayEnabled)
  {
    TargetEncoderCountA = 0;
    TargetEncoderCountB = 0;
    char t[1] = {0};
  }
  else
  {
    char t[1] = {1};
    delay(1000);
    SetOffsetAngle();
    ResetPIDErrors();    
  }  
}

void ResetPIDErrors()
{
  PIDSpeed.ResetErrors();
  PIDGyro.ResetErrors();
  PIDMotorA.ResetErrors();
  PIDMotorB.ResetErrors();
}

void SetOffsetAngle()
{
  long averageAngle = 0;
  for(int n=0; n<10; n++)
  {
    long data = Angle;
    averageAngle += data;
    delay(50);
  }

  OffsetAngle = (averageAngle / 10.0);
}

bool GetSegwayEnabled()
{
  return SegwayEnabled;
}

int LastAngle;

void UpdateSegway()
{

  UpdateAngle();
  //coSpeed = GetCOSpeed(CurrentAngle, LastAngle, CurrentEncoderCountA, CurrentEncoderCountB);
  LastAngle = CurrentAngle;
  //UpdateSpeedAverage(coSpeed);
  //CurrentSpeed = CurrentSpeedBufferAverage;
  //LimitSpeedTargetChange();
  //PIDSpeed.Compute();

  CurrentSpeed = CurrentEncoderCountA + CurrentEncoderCountB;
  CurrentSpeed = UpdateSpeedAverage(CurrentSpeed);
  TargetSpeed = TargetSpeedWanted;
  if(TargetSpeed > 0) {
    TargetSpeed += CurrentSpeed / ((double)ControlSpeedFactor);
    TargetAngle -= TargetSpeed;   
  }
  else if(TargetSpeed < 0) {
    TargetSpeed -= CurrentSpeed / ((double)ControlSpeedFactor);
    TargetAngle += TargetSpeed;    
  }
  else {
    TargetAngle = 0;
  }
  
  //if(CorrectionSpeed > SpeedCorrLimit)
  //  TargetAngle = SpeedCorrLimit;
  //else if(CorrectionSpeed < -SpeedCorrLimit)
  //   TargetAngle = -SpeedCorrLimit;
  //else TargetAngle = CorrectionSpeed;
    
  PIDGyro.Compute();
  
  TargetEncoderCountA = -(CorrectionAngle*GyroOutputFactor);
  TargetEncoderCountB = -(CorrectionAngle*GyroOutputFactor);
  
  LimitTurnSpeedChange();
  SetTargetEncoderWithTurn();
}

double UpdateSpeedAverage(double segwaySpeed)
{
  CurrentSpeedBufferAverage -= CurrentSpeedBuffer[CurrenSpeedBufferIndex];
  CurrentSpeedBuffer[CurrenSpeedBufferIndex] = (segwaySpeed / CurrentSpeedBufferSize);
  CurrentSpeedBufferAverage += CurrentSpeedBuffer[CurrenSpeedBufferIndex];  
  CurrenSpeedBufferIndex++;
  if(CurrenSpeedBufferIndex >= CurrentSpeedBufferSize)
  {
    CurrenSpeedBufferIndex = 0;
  }

  return CurrentSpeedBufferAverage;
}

int TurnSpeedLimit = 12;

void LimitSpeedTargetChange() 
{
  if(TargetSpeed > TargetSpeedWanted)
  {
    TargetSpeed = TargetSpeed - TargetSpeedStepSizeChange;
  }
  else if(TargetSpeed < TargetSpeedWanted)
  {
    TargetSpeed = TargetSpeed + TargetSpeedStepSizeChange;
  }
}

void LimitTurnSpeedChange()
{
  if(TargetTurnSpeed > TargetTurnSpeedWanted)
  {
    TargetTurnSpeed = TargetTurnSpeed - TargetTurnSpeedStepSizeChange;
  }
  else if(TargetTurnSpeed < TargetTurnSpeedWanted)
  {
    TargetTurnSpeed = TargetTurnSpeed + TargetTurnSpeedStepSizeChange;
  }
}

void SetTargetEncoderWithTurn()
{
  if(TargetTurnSpeed != 0)
  {
    if(abs(TargetEncoderCountA) < TurnSpeedLimit)
    {
      TargetEncoderCountA = TargetEncoderCountA + TargetTurnSpeed;
      TargetEncoderCountB = TargetEncoderCountB - TargetTurnSpeed;
      int clipping;
      if(TargetEncoderCountA > TurnSpeedLimit)
      {
        clipping = TargetEncoderCountA - TurnSpeedLimit;
        TargetEncoderCountA = TurnSpeedLimit;
        TargetEncoderCountB = TargetEncoderCountB+clipping;
      }
      if(TargetEncoderCountB > TurnSpeedLimit)
      {
        clipping = TargetEncoderCountB - TurnSpeedLimit;
        TargetEncoderCountB = TurnSpeedLimit;
        TargetEncoderCountA = TargetEncoderCountA-clipping;
      }
      if(TargetEncoderCountA < -TurnSpeedLimit)
      {
        clipping = TargetEncoderCountA + TurnSpeedLimit;
        TargetEncoderCountA = -TurnSpeedLimit;
        TargetEncoderCountB = TargetEncoderCountB+clipping;
      }
      if(TargetEncoderCountB < -TurnSpeedLimit)
      {
        clipping = TargetEncoderCountB + TurnSpeedLimit;
        TargetEncoderCountB = -TurnSpeedLimit;
        TargetEncoderCountA = TargetEncoderCountA-clipping;
      }  
    }
  }
}

void UpdateAngle()
{
  CurrentAngle = (Angle - OffsetAngle);
}

void UpdateGyroPIDSettings()
{  
  PIDGyro.SetTunings(AnglePCorr, AngleICorr, AngleDCorr);
}

void UpdateSpeedPIDSettings()
{  
  PIDSpeed.SetTunings(SpeedPCorr, SpeedICorr, SpeedDCorr);
  PIDSpeed.SetOutputLimits(-SpeedPIDLimit, SpeedPIDLimit);
}
