#define HARDWARECONTROLLER_CPP
#include "HardwareController.h"
#include "Convert.h"
#include <stdexcept>
#include <iostream>

HardwareController::HardwareController(IComPort* comPort) {
    _ComPort = comPort;
    _SendBuffer = new unsigned char[SendBufferLength];
    _ReceiveBuffer = new unsigned char[ReceiveBufferLength];
}

short HardwareController::SendCommand(MotorCommandType commandType, short data) {
    unsigned char data1 = (unsigned char) (data >> 8);
    unsigned char data2 = (unsigned char) (data & 0x00FF);

    return SendCommand(commandType, data1, data2);
}

short HardwareController::SendCommand(MotorCommandType commandType, unsigned char data1, unsigned char data2) {
    unsigned cmd = (unsigned char) commandType;
    bool response = MotorCommandResponse[cmd];
    return SendCommand(cmd, data1, data2, response);
}

short HardwareController::SendCommand(RobotCommandType commandType, short data) {
    unsigned char data1 = (unsigned char) (data >> 8);
    unsigned char data2 = (unsigned char) (data & 0x00FF);

    return SendCommand(commandType, data1, data2);
}

short HardwareController::SendCommand(RobotCommandType commandType, unsigned char data1, unsigned char data2) {
    unsigned cmd = (unsigned char) commandType;
    bool response = RobotCommandResponse[cmd];
    return SendCommand(cmd + RobotCommandTypeOffset, data1, data2, response);
}

short HardwareController::SendCommand(unsigned char cmd, unsigned char data1, unsigned char data2, bool response) {

//    std::cout << "Cmd: " << cmd << " , MSB:" << (int) data1 << " , LSB:" << (int) data2;
    _SendBuffer[0] = cmd;
    _SendBuffer[1] = data1;
    _SendBuffer[2] = data2;

    _ComPort->EmptyReceiveBuffer();

    _ComPort->Send(_SendBuffer, SendBufferLength);

    if (response) {
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
                std::string errorMsg;
                errorMsg = "No response from Arduino. (Cmd: ";
                errorMsg += Convert::IntToString(cmd);
                errorMsg += " , MSB:";
                errorMsg += Convert::IntToString(data1);
                errorMsg += " , LSB:";
                errorMsg += Convert::IntToString(data2);
                
                throw std::invalid_argument(errorMsg);
            }
            _ReceiveBuffer[receiveCount] = receiveChar[0];
        }
//        std::cout << " - Received: " << " MSB:" << (int) _ReceiveBuffer[0] << " , LSB:" << (int) _ReceiveBuffer[1] << std::endl;

        short response = (_ReceiveBuffer[0] << 8);
        response += _ReceiveBuffer[1];
        return response;
    } else
        return 0;
}

HardwareController::~HardwareController() {
    _ComPort->~IComPort();
}