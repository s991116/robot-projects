void ReceiveCommand()
{
  if(CommandFromMasterReceived())
  {
    _CommandFromMaster = ReadCommandFromMaster();
    _DataFromMaster = ReadDataFromMaster();
    _UnhandleCommandFromMasterReceived = true;
  }
}

void HandleCommand()
{
  if(_UnhandleCommandFromMasterReceived)
  {
    SendMessage(_CommandFromMaster, _DataFromMaster);
    _UnhandleCommandFromMasterReceived = false;
    _UnhandleReplyFromMaster = RobotCommandResponse[_CommandFromMaster];
  }
}

void SendCommandReply()
{
  if(_UnhandleReplyFromMaster)
  {
    SendReplyToMaster(_UnhandledResponse);
    _UnhandleReplyFromMaster = false;
  }
}

byte MSB_FromShort(short data) {
  return (data >> 8);
}

byte LSB_FromShort(short data) {
  return (data & 0x00FF);
}

short Bytes_ToShort(byte msb, byte lsb) {
    short data = (msb << 8);
    data |= lsb;
    return data;
}


void SendMessage(byte command, short data)
{
    byte cmd = command;
    switch(cmd)
    {
      case Get_Gyro_YPR: //Gyro Yaw, Pitch, Roll
        _UnhandledResponse = ypr[data]*YPR_Factor;
        return;

      case Get_Gyro_YPR_Accelration: //Accelration Yaw, Pitch, Roll 
        _UnhandledResponse = gyro[data];
        return;
        
      case Set_Gyro_YPR_Factor: //YPR_Factor
        YPR_Factor = data;
        return;
        
      case Get_Distance_cm: //Distance in cm
        _UnhandledResponse = DistanceInCm();
        return;

      case Get_Gyro_YPR_Factor: //YPR_Factor
        _UnhandledResponse = YPR_Factor;
        return;
       
      case Get_Controller_Echo_Command_Test:
        _UnhandledResponse = command;
        return;
        
      case Get_Controller_Echo_Data_Test:
        _UnhandledResponse = data;
        return;

      case Set_Speed_PID_Kp:
        Speed_PID_Kp = ((float)data) / ((float)Speed_PID_Factor);
        return;
        
      case Set_Speed_PID_Ki:
        Speed_PID_Ki = ((float)data) / ((float)Speed_PID_Factor);
        return;
        
      case Set_Speed_PID_Kd:
        Speed_PID_Kd = ((float)data) / ((float)Speed_PID_Factor);
        return;
        
      case Set_Speed_PID_Factor:
        Speed_PID_Factor = data;
        return;

      case Get_Speed_PID_Factor:
        _UnhandledResponse = Speed_PID_Factor;
        return;
        
      case Get_Speed_PID_Kp:
        _UnhandledResponse = Speed_PID_Factor * Speed_PID_Kp;
        return;
        
      case Get_Speed_PID_Ki:
        _UnhandledResponse = Speed_PID_Factor * Speed_PID_Ki;
        return;
        
      case Get_Speed_PID_Kd:
        _UnhandledResponse = Speed_PID_Factor * Speed_PID_Kd;
        return;
        
      case Set_Gyro_PID_Kp:
        Gyro_PID_Kp = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Ki:
        Gyro_PID_Ki = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Kd:
        Gyro_PID_Kd = ((float)data) / ((float)Gyro_PID_Factor);
        return;
        
      case Set_Gyro_PID_Factor:
        Gyro_PID_Factor = data;
        return;

      case Get_Gyro_PID_Factor:
        _UnhandledResponse = Gyro_PID_Factor;
        return;
        
      case Get_Gyro_PID_Kp:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Kp;
        return;
        
      case Get_Gyro_PID_Ki:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Ki;
        return;
        
      case Get_Gyro_PID_Kd:
        _UnhandledResponse = Gyro_PID_Factor * Gyro_PID_Kd;
        return;
        
      case Set_Gyro_State:
        Gyro_PID_Enabled = data;
        return;

      case Get_Gyro_State:
        _UnhandledResponse = Gyro_PID_Enabled;
        return;

      case Set_Gyro_Angle_Offset:
        Gyro_Angle_Offset = data;
        return;
        
      case Get_Gyro_Angle_Offset:
        _UnhandledResponse = Gyro_Angle_Offset;
        return;

      case Set_MotorSpeed:
        SetMotorSpeed(data);
        return;

      case Get_MotorSpeed_Left:
        _UnhandledResponse = MotorSpeedLeft;
        return;

      case Get_MotorSpeed_Right:
        _UnhandledResponse = MotorSpeedRight;
        return;

      case Set_Motor_Max_Speed:
        Motor_max_speed = data;
        return;

      case Get_Motor_Max_Speed:
        _UnhandledResponse = Motor_max_speed;
        return;

      case Set_Motor_State:
        SetMotorState(data);
        return;
        
      case Get_Motor_State:
        _UnhandledResponse = GetMotorState();
        return;
        
      default:
        _UnhandledResponse = ServoCommand(cmd, data);
    }
}

