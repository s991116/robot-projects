#include "SerialBufferMock.h"

SerialBufferMock::SerialBufferMock() {
    BufferIndexStart = 0;
    BufferIndexEnd = 0;
}

int SerialBufferMock::DataAvailable() {
    return BufferIndexEnd-BufferIndexStart;
}

int SerialBufferMock::PeekNextChar() {
    if(DataAvailable() > 0)
    {
        return serialData[BufferIndexStart];
    }
    return -1;
}

int SerialBufferMock::ReadNextChar() {
    if(DataAvailable() > 0)
    {
        char d = serialData[BufferIndexStart];
        BufferIndexStart++;
        return d;
    }
    else
        return -1;
}

void SerialBufferMock::WriteChar(int data) {
    serialData[BufferIndexEnd] = data;
    BufferIndexEnd++;
}

SerialBufferMock::~SerialBufferMock() {
}

