
bool SegwayEnabled = false;
short OffsetAngle;

int AngleError;
float AngleErrorSum;
float AngleErrorDif;
float AngleCorr;
float AnglePCorr = 0.007;
float AngleICorr = 0.002;
float AngleDCorr = 0;

int AngleErrorSumLimit = 100;

void InitializeSegway()
{
}

void SegwayUpdateTime()
{
    AngleError = OffsetAngle - Angle;
    AngleErrorSum = AngleError + AngleErrorSum;
    AngleErrorDif = Angle_Acc;
    if(AngleErrorSum > AngleErrorSumLimit)
    {
      AngleErrorSum = AngleErrorSumLimit;
    }
    else if(AngleErrorSum < -AngleErrorSumLimit)
    {
      AngleErrorSum = -AngleErrorSumLimit;
    }
    AngleCorr = AnglePCorr*AngleError + AngleICorr*AngleErrorSum + AngleDCorr*AngleErrorDif;

  if(SegwayEnabled)
  {
    TargetEncoderCountA = -AngleCorr;
    TargetEncoderCountB = -AngleCorr;
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

