#pragma once

#include "IComPort.h"

class ComPort : public IComPort {
public:
    ComPort();
    virtual ~ComPort();

    int Send(unsigned char* data, int nrOfBytesToSend);
    int ReceiveChar(unsigned char* rx_buffer_ptr);
    void EmptyReceiveBuffer();

private:
    int uart0_filestream;
};