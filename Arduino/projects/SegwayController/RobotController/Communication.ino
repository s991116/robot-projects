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
