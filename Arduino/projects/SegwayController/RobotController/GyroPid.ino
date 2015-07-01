//float Gyro_PID_Kp = 1;
//float Gyro_PID_Ki = 0;
//float Gyro_PID_Kd = 0;
//short Gyro_PID_Factor = 10;
//bool Gyro_PID_Enabled = false;

short AngelIntegration = 0;

short GetPIDSpeed(short Angel, short AngelAccelration)
{
  AngelIntegration += Angel;
  short correction = Gyro_PID_Kp * Angel + Gyro_PID_Kd * AngelAccelration + Gyro_PID_Ki * AngelIntegration;
  return correction;
}
