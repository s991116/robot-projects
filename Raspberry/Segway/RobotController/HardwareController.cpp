#include "HardwareController.h"
#include <stdexcept>
#include <iostream>

HardwareController::HardwareController(IComPort* comPort) {
    _ComPort = comPort;
    _SendBuffer = new unsigned char[SendBufferLength];
    _ReceiveBuffer = new unsigned char[ReceiveBufferLength];
}

short HardwareController::SendCommand(CommandType commandType, short data) {
    unsigned char data1 = (unsigned char) (data >> 8);
    unsigned char data2 = (unsigned char) (data & 0x00FF);

    return SendCommand(commandType, data1, data2);
}

short HardwareController::SendCommand(CommandType commandType, unsigned char data1, unsigned char data2) {
    unsigned cmd = (unsigned char) commandType;
    //std::cout << "Cmd: " << cmd << " , MSB:" << (int) data1 << " , LSB:" << (int) data2;
    _SendBuffer[0] = cmd;
    _SendBuffer[1] = data1;
    _SendBuffer[2] = data2;

    _ComPort->EmptyReceiveBuffer();

    _ComPort->Send(_SendBuffer, SendBufferLength);

    unsigned char* receiveChar = new unsigned char[1];
    for (short receiveCount = 0; receiveCount < ReceiveBufferLength; receiveCount++) {
        int result = 0;
        int retryCount = 0;
        do {
            result = _ComPort->ReceiveChar(receiveChar);
            retryCount++;
            if (result != 1) {
                usleep(25000); //Wait 25 ms
            }
        } while (result != 1 && retryCount < _MaxRetryCount);
        if (retryCount == _MaxRetryCount) {
            throw std::invalid_argument("No response from Arduino.");
        }
        _ReceiveBuffer[receiveCount] = receiveChar[0];
    }
    //std::cout << " - Received: " << " MSB:" << (int) _ReceiveBuffer[0] << " , LSB:" << (int) _ReceiveBuffer[1] << std::endl;

    short response = (_ReceiveBuffer[0] << 8);
    response += _ReceiveBuffer[1];
    return response;
}

HardwareController::~HardwareController() {
    _ComPort->~IComPort();
}