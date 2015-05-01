#pragma once

#include "ComPort.h"
#include "CommandType.h"

class Controller
{
public:
	Controller(ComPort* comPort);
	
	short SendCommand(CommandType commandType, short data);
	short SendCommand(CommandType commandType, unsigned char data1, unsigned char data2);

	~Controller();

private:
	ComPort* _ComPort;
	unsigned char* _SendBuffer;
	static const short SendBufferLength = 3;
	unsigned char* _ReceiveBuffer;
	static const short ReceiveBufferLength = 2;
	unsigned char* _ReceiveChar;
};