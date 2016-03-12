short AngleIntegration = 0;

void UpdateSegwayPosition()
{
  unsigned long StartTime = millis();
  if(((StartTime - UpdatePositionTime) >= PID_Looptime_ms) && Gyro_PID_Enabled)
  {
    UpdatePositionTime = StartTime;
    short angle = ypr[1]*YPR_Factor + Gyro_Angle_Offset;
    short angleAccelration = gyro[1];
    MeasuredSpeed = GetCurrentSpeed();
    short angleOffset = GetPIDAngle(SpeedOffset, MeasuredSpeed);
    short speed = GetPIDSpeed(angleOffset, angle, angleAccelration);
    SetMotorSpeed(speed);
  }
}

short GetPIDAngle(short Desired, short Measured)
{
  short error = Desired - Measured;
  SpeedIntegration += error;
  short SpeedDiff = Measured - Measured_Old;
  short correction = Speed_PID_Kp * error + Speed_PID_Kd * SpeedDiff + Speed_PID_Ki * SpeedIntegration;
  Measured_Old = Measured;
  return correction;
}

short GetPIDSpeed(short DesiredAngle, short MeasuredAngle, short AngleAccelration)
{
  short AngleError = DesiredAngle - MeasuredAngle;
  AngleIntegration += AngleError;
  short correction = Gyro_PID_Kp * AngleError + Gyro_PID_Kd * AngleAccelration + Gyro_PID_Ki * AngleIntegration;
  return correction;
}
