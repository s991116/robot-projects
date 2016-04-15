#ifndef SerialProtocol
#define SerialProtocol
#include "CommandTypes.h"
#include "ComStream.h"
#include "CommunicationHandler.h"
#include "CommandType.h"

class SerialCommandProtocol
{
  public:
	  SerialCommandProtocol(ComStream *serial, 	  
          CommunicationHandler* communicationHandler);

          void sendCommand(HardwareControllerCommand commandID);
	  void sendCommand(unsigned char commandID);
          void sendCommandAndData(HardwareControllerCommandTypeByte commandID, unsigned char payload);
          void sendCommandAndData(HardwareControllerCommandTypeShort commandID, char16_t payload);
	  void sendCommandAndData(unsigned char commandID, unsigned char payload);
	  void sendCommandAndData(unsigned char commandID, char16_t payload);

	  char16_t getShortData(HardwareControllerCommandTypeShort id);
	  char16_t getShortData(unsigned char commandID);
          short getShortSignedData(unsigned char commandID);
          short getShortSignedData(HardwareControllerCommandTypeShort id);

          unsigned char getByteData(HardwareControllerCommandTypeByte id);
	  unsigned char getByteData(unsigned char commandID);
      
	  void handleResponse();
          CommunicationHandler* _CommunicationHandler;

  private:
	  void createAndSendCommand(unsigned char commandID, unsigned char commandType);
	  unsigned char createCommand(unsigned char commandID, unsigned char commandType);
	  
	  void createReplyAndSend(unsigned char commandType, unsigned char reply);
	  void createReplyAndSend(unsigned char commandType, char16_t reply);
	  
	  bool handleResponseAndReply(char16_t *data);

	  void sendByte(unsigned char data);
	  unsigned char getByte();
		  
	  void sendDataShort(char16_t payload);
	  char16_t getDataShort();
	  
	  void sendDataByte(unsigned char data);
	  unsigned char getDataByte();
	  
	  unsigned char waitGetByte();
	  
	  ComStream *_Serial;
	  void (*_HandleCommand)(unsigned char commandId);
	  void (*_HandleData)(unsigned char responseType, unsigned char commandId, char16_t data);
	  char16_t (*_HandleReply)(unsigned char responseType, unsigned char commandId);
};
#endif