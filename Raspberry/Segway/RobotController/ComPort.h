#pragma once

#include "IComPort.h"

class ComPort : public IComPort {
public:
    ComPort();
    virtual ~ComPort();

    int Send(unsigned char* data, int nrOfBytesToSend);
    int Send(unsigned char data);
    int ReceiveChar(unsigned char* rx_buffer_ptr);
    int ReceiveChar();
    void EmptyReceiveBuffer();
private:
    int uart0_filestream;
};