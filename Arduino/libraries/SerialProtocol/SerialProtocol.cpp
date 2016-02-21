#include "SerialProtocol.h"


SerialCommandProtocol::SerialCommandProtocol(Stream *serial, void (*handleCommand)(uint8_t commandId), void (*handleData)(uint8_t responseType, uint8_t commandId, uint16_t data), uint16_t (*handleReply)(uint8_t responseType, uint8_t commandId))
{
	_Serial = serial;
	_HandleCommand = handleCommand;
	_HandleData = handleData;
	_HandleReply = handleReply;
}

/// <summary>
/// commandID 0-31
/// </summary>
void SerialCommandProtocol::sendCommandAndData(uint8_t commandID, uint8_t payload)
{
	createAndSendCommand(commandID, COMMAND_DATA_BYTE_NO_REPLY);
	sendDataByte(payload);
}

/// <summary>
/// commandID 0-31
/// </summary>
void SerialCommandProtocol::sendCommandAndData(uint8_t commandID, int16_t payload)
{
	createAndSendCommand(commandID, COMMAND_DATA_SHORT_NO_REPLY);
	sendDataShort(payload);
}

/// <summary>
/// commandID 0-31
/// </summary>
void SerialCommandProtocol::sendCommand(uint8_t commandID)
{
	createAndSendCommand(commandID,COMMAND_NO_DATA_NO_REPLY);
}

uint16_t SerialCommandProtocol::getShortData(uint8_t commandID)
{
	createAndSendCommand(commandID,COMMAND_NO_DATA_SHORT_REPLY);
	uint16_t response;
	while(!handleResponseAndReply(&response));
	return response;
}

uint8_t SerialCommandProtocol::getByteData(uint8_t commandID)
{
	createAndSendCommand(commandID,COMMAND_NO_DATA_BYTE_REPLY);
	uint16_t response;
	while(!handleResponseAndReply(&response));
	return response;
}

void SerialCommandProtocol::handleResponse()
{
	uint16_t *data;
	handleResponseAndReply(data);
}

bool SerialCommandProtocol::handleResponseAndReply(uint16_t *data)
{
	if(_Serial->available() == 0)
		return false;
	
	uint8_t response = _Serial->read();
	uint8_t responseType = (response & COMMAND_REPLY_FILTER);
	uint8_t responseCommandId = (response & COMMAND_ID_FILTER);
	switch(responseType)
	{
		case REPLY_BYTE:
		  *data = getDataByte();
	  	  return true;
		  
		case REPLY_SHORT:
		  *data = getDataShort();
	  	  return true;
		  
		case COMMAND_DATA_BYTE_NO_REPLY:
		{
  		  uint8_t responseDataByte = getDataByte();
  		  _HandleData(responseType, responseCommandId, responseDataByte);
  		  return false;			
		}
 
		case COMMAND_DATA_SHORT_NO_REPLY:
		{
  	      uint16_t responseDataShort = getDataShort();
  	      _HandleData(responseType, responseCommandId, responseDataShort);
  		  return false;			
		}
		
		case COMMAND_NO_DATA_NO_REPLY:
		{
           _HandleCommand(responseCommandId);
  		  return false;			
		}
		
		case COMMAND_NO_DATA_BYTE_REPLY:
		{
          uint8_t replyByte = _HandleReply(responseType, responseCommandId);
  		  createReplyAndSend(REPLY_BYTE, replyByte);
  		  return false;			
		}
		  
		case COMMAND_NO_DATA_SHORT_REPLY:
		{
  		  uint16_t replyShort = _HandleReply(responseType, responseCommandId);
          createReplyAndSend(REPLY_BYTE, replyShort);
  		  return false;  			
		}
	}
	return true;
}

void SerialCommandProtocol::createReplyAndSend(uint8_t commandType, uint8_t reply)
{
	createAndSendCommand(0, commandType);
	sendDataByte(reply);
}

void SerialCommandProtocol::createReplyAndSend(uint8_t commandType, uint16_t reply)
{
	createAndSendCommand(0, commandType);
	sendDataShort(reply);
}

void SerialCommandProtocol::createAndSendCommand(uint8_t commandID, uint8_t commandType)
{
	uint8_t command = createCommand(commandID, commandType);
	sendByte(command);
}

uint8_t SerialCommandProtocol::createCommand(uint8_t commandID, uint8_t commandType)
{
	return ((commandID & COMMAND_ID_FILTER) | commandType);
}

void SerialCommandProtocol::sendByte(uint8_t data)
{
	_Serial->write(data);
}

uint8_t SerialCommandProtocol::waitGetByte()
{
	while(_Serial->available() == 0);
	return _Serial->read();
}

int16_t SerialCommandProtocol::getDataShort()
{
	uint8_t high = getDataByte();
	uint8_t low = getDataByte();	
	int16_t result = ((((int16_t)high) << 8) | low);
	return result;
}

void SerialCommandProtocol::sendDataShort(int16_t data)
{   
	uint8_t high = (data >> 8);
	uint8_t low = data & 0xFF;	
	sendDataByte(high);
    sendDataByte(low);
}

void SerialCommandProtocol::sendDataByte(uint8_t data)
{
	uint8_t high = (data >> 4);
	uint8_t low = data & 0x0F;
	_Serial->write(high);
	_Serial->write(low);
}

uint8_t SerialCommandProtocol::getDataByte()
{
	uint8_t high = waitGetByte();
	uint8_t low =  waitGetByte();	
	uint8_t result = ((high << 4) | low);	
	return result;
}

