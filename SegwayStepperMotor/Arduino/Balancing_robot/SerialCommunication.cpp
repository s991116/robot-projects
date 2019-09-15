#include "SerialCommunication.h"
#include "SerialCommands.h"

SerialCommunication::SerialCommunication(HardwareSerial *serial, receiveFunctionsP receiveFunctions, transmitFunctionsP transmitFunctions) {
    this->uart = serial;
    this->_receiveFunctions = receiveFunctions;
    this->_transmitFunctions = transmitFunctions;
}

void SerialCommunication::Initialize() {
    this->uart->begin(9600);
}

void SerialCommunication::HandleCommunication() {
    if(uart->available()>0){
        unsigned char data = this->uart->read();
        unsigned char cmdType = data >> 4;
        unsigned char cmd = data & 0x0F;
        unsigned char receivedData;

        switch(cmdType) {
            case CMD_TYPE_SET_VALUE:
                while(this->uart->available() == 0);
                receivedData = uart->read();
                this->_receiveFunctions[cmd](receivedData);
                break;

            case CMD_TYPE_GET_VALUE:
                data = this->_transmitFunctions[cmd]();
                this->uart->write(data);
                break;
        }
    }
}