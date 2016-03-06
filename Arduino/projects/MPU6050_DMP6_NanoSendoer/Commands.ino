void handleCommand(uint8_t commandId)
{  
}

void handleData(uint8_t responseType, uint8_t commandId, int16_t data)
{
  switch(responseType)
  {
    case COMMAND_DATA_BYTE_NO_REPLY:
      switch(commandId)
      {
        case 0:
          SetSendMode(data);
          break;
      }
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
      break;
  }
}

int16_t handleReply(uint8_t responseType, uint8_t commandId)
{
  switch(responseType)
  {
    case COMMAND_NO_DATA_BYTE_REPLY:
      break;
    
    case COMMAND_NO_DATA_SHORT_REPLY:
      switch(commandId)
      {
        case 0:
          return angle;
          
        case 1:
          return angle_acc;
      }
      break;    
  }
  return 0;
}

SerialCommandProtocol serialCommand(&Serial, handleCommand, handleData, handleReply);

void HandleCommands()
{
  serialCommand.handleResponse();
}

void SendAngleData(short angle, short angle_acc)
{
  serialCommand.sendCommandAndData(0, angle);
  serialCommand.sendCommandAndData(1, angle_acc);
}

