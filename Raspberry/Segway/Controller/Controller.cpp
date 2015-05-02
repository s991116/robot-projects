#include "Controller.h"
#include "iostream"


Controller::Controller(ComPort* comPort)
{
	_ComPort = comPort;
	_SendBuffer = new unsigned char[SendBufferLength];
	_ReceiveBuffer = new unsigned char[ReceiveBufferLength];
}

short Controller::SendCommand(CommandType commandType, short data)
{
	std::cout << "data (short): " << (int)(data) << std::endl;
	unsigned char data1 = (unsigned char)(data & 0x00FF);
	unsigned char data2 = (unsigned char)(data >> 8);
	std::cout << "data1: " << (int)(data1) << std::endl;
	std::cout << "data2: " << (int)(data2) << std::endl;
	std::cout << "cmd:   " << (int)(commandType) << std::endl;

	return SendCommand(commandType, data1, data2);
}

short Controller::SendCommand(CommandType commandType, unsigned char data1, unsigned char data2)
{
	_SendBuffer[0] = (unsigned char)commandType;
	_SendBuffer[1] = data1;
	_SendBuffer[2] = data2;

	_ComPort->Send(_SendBuffer, SendBufferLength);

	unsigned char* receiveChar = new unsigned char[1];
	for (short receiveCount = 0; receiveCount < ReceiveBufferLength; receiveCount++)
	{
		int result = 0;
		do{
			result = _ComPort->ReceiveChar(receiveChar);
		} while (result != 1);
		_ReceiveBuffer[receiveCount] = receiveChar[0];
	}

	short response = (_ReceiveBuffer[1] << 8);
	response += _ReceiveBuffer[0];
	std::cout << "response: " << (int)(response) << std::endl;

	return response;
}

Controller::~Controller()
{
	_ComPort->~ComPort();
}