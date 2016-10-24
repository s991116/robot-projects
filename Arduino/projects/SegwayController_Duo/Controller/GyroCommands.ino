
short Angle;
short Angle_Acc;

void handleDataChar(char commandId, char length, char data[]) {
}

void handleDataShort(char commandId, char length, short data[]) {
  switch(commandId)
      {
        case 0:
          Angle = data[0];
          Angle_Acc = data[1];
          break;
      }
}

void handleReplyChar(char commandId, char length, char data[]) {
}

void handleReplyShort(char commandId, char length, short data[]) {
}


ArduinoDataHandler dataHandler(handleDataChar, handleDataShort, handleReplyChar, handleReplyShort);
MessageDataProtocol messageDataProtocol = MessageDataFactory::Create(&Serial3, &dataHandler);



void InitializeGyro()
{
  Serial3.begin(115200);
  delay(500);
}

void serialFlush(){
  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
}   

void HandleGyroCommands()
{
  messageDataProtocol.Update();
}

short GetAngle()
{
  return messageDataProtocol.RequestCharData(0);
}
