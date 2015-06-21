#pragma once
	class IComPort
	{
	public:
		virtual int Send(unsigned char* data, int nrOfBytesToSend) = 0;
		virtual int ReceiveChar(unsigned char* rx_buffer_ptr) = 0;
	};