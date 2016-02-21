
short Angle;
short Angle_Acc;

void handleCommand(uint8_t commandId)
{
}

void handleData(uint8_t responseType, uint8_t commandId, uint16_t data)
{
  switch(responseType)
  {
    case COMMAND_DATA_BYTE_NO_REPLY:
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
      switch(commandId)
      {
        case 0:
          Angle = data;
          break;

        case 1:
          Angle_Acc = data;
          break;
      }
      break;
  }
}

uint16_t handleReply(uint8_t responseType, uint8_t commandId)
{
  switch(responseType)
  {
    case COMMAND_NO_DATA_BYTE_REPLY:
      return 13;
      break;
    
    case COMMAND_NO_DATA_SHORT_REPLY:
      return 17;
      break;    
  }
  return 0;
}

SerialCommandProtocol serialCommand(&Serial3, handleCommand, handleData, handleReply);

void InitializeGyro()
{
  Serial3.begin(115200);
  serialFlush();
}

void serialFlush(){
  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
}   

void HandleGyroCommands()
{
  serialCommand.handleResponse();
}
