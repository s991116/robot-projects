void handleCommand(uint8_t commandId)
{
  Serial.print("Command Received for command id:");
  Serial.print(commandId);
}

void handleData(uint8_t responseType, uint8_t commandId, uint16_t data)
{
  switch(responseType)
  {
    case COMMAND_DATA_BYTE_NO_REPLY:
    Serial.print("Byte Received for command id:");
    Serial.print(commandId);
    Serial.print(" , data: ");
    Serial.println(data);
      break;
       
    case COMMAND_DATA_SHORT_NO_REPLY:
    Serial.print("Short Received for command id:");
    Serial.print(commandId);
    Serial.print(" , data: ");
    Serial.println(data);
    switch(commandId)
    {
      case 0:
        Angle = data;
        break;

      case 1:
        AngleAcc = data;
        break;
    }
    break;
  }
}

uint16_t handleReply(uint8_t responseType, uint8_t commandId)
{
  Serial.print("Handle reply received for command id:");
  Serial.println(commandId);

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

void HandleCommands()
{
  serialCommand.handleResponse();
/*  
  while(Serial3.available() > 0)
  {
    int data = Serial3.read();
    Serial.println(data);
  }
*/  
}
