#include "HardwareController.h"
#include <stdexcept>

HardwareController::HardwareController(IComPort* comPort)
{
	_ComPort = comPort;
	_SendBuffer = new unsigned char[SendBufferLength];
	_ReceiveBuffer = new unsigned char[ReceiveBufferLength];
}

short HardwareController::SendCommand(CommandType commandType, short data)
{
	unsigned char data1 = (unsigned char)(data & 0x00FF);
	unsigned char data2 = (unsigned char)(data >> 8);

	return SendCommand(commandType, data1, data2);
}

short HardwareController::SendCommand(CommandType commandType, unsigned char data1, unsigned char data2)
{
	_SendBuffer[0] = (unsigned char)commandType;
	_SendBuffer[1] = data1;
	_SendBuffer[2] = data2;

	_ComPort->Send(_SendBuffer, SendBufferLength);

	unsigned char* receiveChar = new unsigned char[1];
	for (short receiveCount = 0; receiveCount < ReceiveBufferLength; receiveCount++)
	{
		int result = 0;
		int retryCount = 0;
		do{
			result = _ComPort->ReceiveChar(receiveChar);
			retryCount++;
			if (result != 1)
			{
				usleep(10000); //Wait 10 ms
			}
		} while (result != 1 && retryCount < _MaxRetryCount);
		if (retryCount == _MaxRetryCount)
		{
			throw std::invalid_argument("No response from Arduino.");
		}
		_ReceiveBuffer[receiveCount] = receiveChar[0];
	}

	short response = (_ReceiveBuffer[1] << 8);
	response += _ReceiveBuffer[0];
	return response;
}

HardwareController::~HardwareController()
{
	_ComPort->~IComPort();
}