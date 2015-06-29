#pragma once

#include "IComPort.h"
#include "CommandType.h"

class HardwareController {
public:
    HardwareController(IComPort* comPort);

    short SendCommand(MotorCommandType commandType, short data);
    short SendCommand(MotorCommandType commandType, unsigned char data1, unsigned char data2);
    short SendCommand(RobotCommandType commandType, unsigned char data1, unsigned char data2);
    short SendCommand(RobotCommandType commandType, short data);

    
    ~HardwareController();

private:
    short SendCommand(unsigned char cmd, unsigned char data1, unsigned char data2, bool response);

    IComPort* _ComPort;
    unsigned char* _SendBuffer;
    static const short SendBufferLength = 3;
    unsigned char* _ReceiveBuffer;
    static const short ReceiveBufferLength = 2;
    unsigned char* _ReceiveChar;
    static const int _MaxRetryCount = 100;
};