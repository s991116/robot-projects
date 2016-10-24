#include <ArduinoDataHandler.h>
#include <ArduinoSerial.h>
#include <DataHandler.h>
#include <DataHandlerInterface.h>
#include <DataPackets.h>
#include <MessageDataProtocol.h>
#include <SerialCom.h>
#include <MessageDataFactory.h>

void handleDataChar(char commandId, char length, char data[]) {
      switch(commandId)
      {
        case 0:
          SetSendMode(data[0]);
          break;
      }
}

void handleDataShort(char commandId, char length, short data[]) {
}

void handleReplyChar(char commandId, char length, char data[]) {
}

void handleReplyShort(char commandId, char length, short data[]) {
      switch(commandId)
      {
        case 0:
          data[0] = angle;
          break;
          
        case 1:
          data[0] = angle_acc;
          break;
      }
}


ArduinoDataHandler dataHandler(handleDataChar, handleDataShort, handleReplyChar, handleReplyShort);
MessageDataProtocol serialCommand = MessageDataFactory::Create(&Serial, &dataHandler);

//----------------------------------------------------

void HandleCommands()
{
  serialCommand.Update();
}

void SendAngleData(short angle, short angle_acc)
{
  short data[2] = {angle, angle_acc};
  serialCommand.SendData(0, 2, data);
}

