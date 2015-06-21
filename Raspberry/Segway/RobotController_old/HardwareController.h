#pragma once

#include "IComPort.h"
#include "CommandType.h"

class HardwareController {
public:
    HardwareController(IComPort* comPort);

    short SendCommand(CommandType commandType, short data);
    short SendCommand(CommandType commandType, unsigned char data1, unsigned char data2);

    ~HardwareController();

private:
    IComPort* _ComPort;
    unsigned char* _SendBuffer;
    static const short SendBufferLength = 3;
    unsigned char* _ReceiveBuffer;
    static const short ReceiveBufferLength = 2;
    unsigned char* _ReceiveChar;
    static const int _MaxRetryCount = 50;
};