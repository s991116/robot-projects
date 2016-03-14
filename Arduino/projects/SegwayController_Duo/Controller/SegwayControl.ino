
bool SegwayEnabled = false;
short OffsetAngle;

float AngleError;
float AngleErrorSum;
float AngleErrorDif;
float AngleCorr;
float AnglePCorr = 1.8;
float AngleICorr = 0.0001;
float AngleDCorr = 0;

float AngleCorrFactor = 0.01;

int AngleErrorSumLimit = 15000;
int AngleErrorSumCorrLimit = 1500;

float TurnSpeed = 0;

void InitializeSegway()
{
}

bool GetSegwayEnabled()
{
  return SegwayEnabled;
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
    delay(50);
    SetOffsetAngle();    
  }  
}

void SegwayUpdateTime()
{
    AngleError = OffsetAngle - Angle;
    AngleErrorSum = (AngleError * AngleICorr) + AngleErrorSum;
    AngleErrorDif = Angle_Acc;
        
    if(AngleErrorSum > AngleErrorSumLimit)
    {
      AngleErrorSum = AngleErrorSumLimit;
    }
    else if(AngleErrorSum < -AngleErrorSumLimit)
    {
      AngleErrorSum = -AngleErrorSumLimit;
    }

    float AngleErrorSumCorrLimited = AngleErrorSum;
    if(AngleErrorSumCorrLimited > AngleErrorSumCorrLimit)
    {
      AngleErrorSumCorrLimited = AngleErrorSumCorrLimit;
    }
    else if(AngleErrorSumCorrLimited < -AngleErrorSumCorrLimit)
    {
      AngleErrorSumCorrLimited = -AngleErrorSumCorrLimit;
    }
    
    AngleCorr = AnglePCorr*AngleError + AngleErrorSumCorrLimited + AngleDCorr*AngleErrorDif;
    AngleCorr = AngleCorr * AngleCorrFactor;
  if(SegwayEnabled)
  {
    TargetEncoderCountA = (-AngleCorr) + TurnSpeed;
    TargetEncoderCountB = (-AngleCorr) - TurnSpeed;
  }
  else
  {
    AngleErrorSum = 0;
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

