//float Gyro_PID_Kp = 1;
//float Gyro_PID_Ki = 0;
//float Gyro_PID_Kd = 0;
//short Gyro_PID_Factor = 10;
//bool Gyro_PID_Enabled = false;

short AngleIntegration = 0;

short GetPIDSpeed(short Angle, short AngleAccelration)
{
  AngleIntegration += Angle;
  short correction = Gyro_PID_Kp * Angle + Gyro_PID_Kd * AngleAccelration + Gyro_PID_Ki * AngleIntegration;
  return -correction;
}
