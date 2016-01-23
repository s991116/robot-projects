int SpeedToInterruptDelay(int speed)
{
  return MeasureTimePeriod / speed;
}

void UpdateSpeedMeasure()
{
  UpdateSpeedMesaure(&EncoderAInterruptTime, &EncoderAInterruptPeriod);
  UpdateSpeedMesaure(&EncoderBInterruptTime, &EncoderBInterruptPeriod);
}

void UpdateSpeedMesaure(volatile long *encoderInterruptTime, volatile long *encoderInterruptPeriod)
{
  if(micros() > *encoderInterruptTime + MeasureTimePeriod)
  {
    *encoderInterruptPeriod = 0;
  }
}

