#ifndef SerialProtocol
#define SerialProtocol
#include <Arduino.h>
#include <Stream.h>
#include "CommandTypes.h"

class SerialCommandProtocol
{
  public:
	  SerialCommandProtocol(Stream *serial, 	  
	    void (*handleCommand)(uint8_t commandId),
	    void (*handleData)(uint8_t responseType, uint8_t commandId, int16_t data),
	    int16_t (*handleReply)(uint8_t responseType, uint8_t commandId));

	  void sendCommand(uint8_t commandID);
	  void sendCommandAndData(uint8_t commandID, uint8_t payload);
	  void sendCommandAndData(uint8_t commandID, int16_t payload);

	  int16_t getShortData(uint8_t commandID);
	  uint8_t getByteData(uint8_t commandID);
      
	  void handleResponse();

  private:
	  void createAndSendCommand(uint8_t commandID, uint8_t commandType);
	  uint8_t createCommand(uint8_t commandID, uint8_t commandType);
	  
	  void createReplyAndSend(uint8_t commandType, uint8_t reply);
	  void createReplyAndSend(uint8_t commandType, int16_t reply);
	  
	  bool handleResponseAndReply(int16_t *data);

	  void sendByte(uint8_t data);
	  uint8_t getByte();
		  
	  void sendDataShort(int16_t payload);
	  int16_t getDataShort();
	  
	  void sendDataByte(uint8_t data);
	  uint8_t getDataByte();
	  
	  uint8_t waitGetByte();
	  
	  Stream *_Serial;
	  void (*_HandleCommand)(uint8_t commandId);
	  void (*_HandleData)(uint8_t responseType, uint8_t commandId, int16_t data);
	  int16_t (*_HandleReply)(uint8_t responseType, uint8_t commandId);

};
#endif