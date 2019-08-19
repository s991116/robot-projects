#include "SerialCommunication.h"
#include "SerialCommands.h"

SerialCommunication::SerialCommunication(HardwareSerial *serial) {
    this->uart = serial;
    this->uart->begin(9600);                                                       //Start the serial port at 9600 kbps
    this->uart->println("Setup started.");

    this->_waitingForData = false;
}

void SerialCommunication::ReceiveData() {
    if(uart->available()>0){                                                   //If there is serial data available
        byte cmd = this->uart->read();
        byte cmdType = cmd >> 4;
        switch(cmdType) {
            case 0:
                this->_navigationReceived = cmd;                                     //Load the received serial data in the navigationReceived variable
                this->_navigationReceiveCounter = 0;                                                    //Reset the receive_counter variable
                this->_recivedCmd = cmd;
                break;

            case 1:
                this->_recivedCmd = cmd;
                while(this->uart->available() == 0);
                this->_receivedData = uart->read();
                break;

            case 2:
                this->_recivedCmd = cmd;
                this->_waitingForData = true;
                break;
        }
    }
  if(_navigationReceiveCounter <= 25)_navigationReceiveCounter ++;                              //The received byte will be valid for 25 program loops (100 milliseconds)
  else _navigationReceiveCounter = 0x00;                                                //After 100 milliseconds the received byte is deleted 
}

byte SerialCommunication::GetNavigation() {
    return this->_navigationReceived;
}

byte SerialCommunication::GetReceivedCmd() {
    return this->_recivedCmd;
}

byte SerialCommunication::GetReceivedData() {
    return this->_receivedData;
}

void SerialCommunication::SendData(byte data) {
    if(this->_waitingForData) {
        this->uart->write(data);
        this->_waitingForData = false;
    }
}