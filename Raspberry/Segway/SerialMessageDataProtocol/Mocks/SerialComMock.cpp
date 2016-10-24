#include "SerialComMock.h"

SerialComMock::SerialComMock() {
    _BufferStartIndex = 0;
    _BufferEndIndex = 0;
}

void SerialComMock::SetOppositeSerial(SerialComMock* oppositeSerial) {
    _OppositeSerial = oppositeSerial;
}

SerialComMock::~SerialComMock() {
}

int SerialComMock::DataAvailable() {    
    return _BufferEndIndex - _BufferStartIndex;
}

int SerialComMock::PeekNextChar() {
    if(DataAvailable() > 0)
    {
        return _Buffer[_BufferStartIndex];
    }
    return -1;
}

int SerialComMock::ReadNextChar() {
    if(DataAvailable() > 0)
    {
        int d = _Buffer[_BufferStartIndex];
        _BufferStartIndex++;
        return d;
    }
    else
        return -1;
}

void SerialComMock::WriteChar(int data) {
    _OppositeSerial->AppendDataToBuffer(data);
    return;
}

void SerialComMock::AppendDataToBuffer(int data) {
    _Buffer[_BufferEndIndex] = data;
    _BufferEndIndex++;    
}