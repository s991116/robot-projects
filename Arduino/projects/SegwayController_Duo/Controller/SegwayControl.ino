
bool SegwayEnabled = true;
short OffsetAngle;

float AngleError;
float AngleErrorSum;
float AngleErrorDif;
float AngleCorr;
float AnglePCorr = 1.8;
float AngleICorr = 0.0001;
float AngleDCorr = 0;

float AngleCorrFactor = 0.01;

int AngleErrorSumLimit = 1500;

void InitializeSegway()
{
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
    
    AngleCorr = AnglePCorr*AngleError + AngleErrorSum + AngleDCorr*AngleErrorDif;
    AngleCorr = AngleCorr * AngleCorrFactor;
  if(SegwayEnabled)
  {
    TargetEncoderCountA = -AngleCorr;
    TargetEncoderCountB = -AngleCorr;
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

