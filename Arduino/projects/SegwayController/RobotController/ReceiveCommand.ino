void ReceiveCommand()
{
  if(!_UnhandleCommandReceivedFromMaster && UnhandledCommandFromMasterReceived())
  {
    _CommandFromMaster = ReadCommandFromMaster();
    _DataFromMaster = ReadDataFromMaster();
    _UnhandleCommandReceivedFromMaster = true;
  }
}

void HandleCommand()
{
  if(_UnhandleCommandReceivedFromMaster)
  {
    SendMessage(_CommandFromMaster, _DataFromMaster);
    _UnhandleCommandReceivedFromMaster = false;
    if(MotorControllerCommand(_CommandFromMaster))
    {
      _UnhandledResponseFromMotorController = MotorCommandResponse[_CommandFromMaster];
      _CommandSentTime = millis();
    }
    else
    {
      _UnhandledResponseFromRobotController = RobotCommandResponse[_CommandFromMaster-RobotCommandTypeOffset];
    }
  }
}

bool MotorControllerCommand(byte command)
{
  return (command < 128);
}

bool UnhandledCommandFromMasterReceived()
{
  return (Serial.available() >= 3);
}

byte ReadCommandFromMaster()
{
  return Serial.read();
}

short ReadDataFromMaster()
{
  byte msb = Serial.read();
  byte lsb = Serial.read();
  return Bytes_ToShort(msb, lsb);
}

void SendCommandReply()
{
  if(_UnhandledResponseFromRobotController)
  {
    SendReplyToMaster(_UnhandledResponse);
    _UnhandledResponseFromRobotController = false;
  }
  else if(_UnhandledResponseFromMotorController && MotorControllerResponseTimePassed())
  {
    _UnhandledResponse = GetReplyFromMotorController();
    SendReplyToMaster(_UnhandledResponse);
    _UnhandledResponseFromMotorController = false;
  }
}

void SendReplyToMaster(short reply)
{
  Serial.write(MSB_FromShort(reply));
  Serial.write(LSB_FromShort(reply));  
}

#define unsigned_long_max (4294967295)
#define MinMotorControllerResponseTime (4) //in milliseconds

bool MotorControllerResponseTimePassed() {
  unsigned long currentTime = millis();
  if(currentTime > _CommandSentTime)
  {
    return ((currentTime - _CommandSentTime) >= MinMotorControllerResponseTime);
  }
  else
  {
    return ((unsigned_long_max - _CommandSentTime + currentTime) >= MinMotorControllerResponseTime);
  }
}

