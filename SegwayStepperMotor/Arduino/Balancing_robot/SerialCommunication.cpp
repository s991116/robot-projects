#include "SerialCommunication.h"
#include "SerialCommands.h"

SerialCommunication::SerialCommunication(HardwareSerial *serial, receiveFunctionsP receiveFunctions, transmitFunctionsP transmitFunctions, navigationFunctionP navigationFunction) {
    this->uart = serial;
    this->_receiveFunctions = receiveFunctions;
    this->_transmitFunctions = transmitFunctions;
    this->_navigationFunction = navigationFunction;
}

void SerialCommunication::Initialize() {
    this->uart->begin(115200);
    this->_state = State::getCmd;
}

void SerialCommunication::HandleCommunication() {
    switch(this->_state)
    {
        case State::getCmd:
            if(uart->available()>0){
                unsigned char data = this->uart->read();
                this->_cmdType = data >> 6;
                this->_cmd = data & 0x3F;
                this->_state = State::handleCmd;
            }
            break;

        case State::handleCmd:
            switch(this->_cmdType) {
                case CMD_TYPE_SET_VALUE:
                    while(this->uart->available() == 0);
                    this->_receivedData = uart->read();
                    this->_receiveFunctions[this->_cmd](this->_receivedData);
                    this->_state = State::getCmd;
                    break;

                case CMD_TYPE_NAVIGATION:
                    this->_navigationFunction(this->_cmd);
                    this->_state = State::getCmd;
                    break;

                case CMD_TYPE_GET_VALUE:
                    this->_data = this->_transmitFunctions[this->_cmd]();
                    this->_state = State::respond;
                    break;
            }            
            break;

        case State::respond:
            this->uart->write(this->_data);
            this->_state = State::getCmd;
            break;
    }
}