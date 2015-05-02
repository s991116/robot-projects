#pragma once
class ComPort
{
public:
	ComPort();
	virtual ~ComPort();

	int Send(unsigned char* data, int nrOfBytesToSend);
	int ReceiveChar(unsigned char* rx_buffer_ptr);

private:
	int uart0_filestream;
};