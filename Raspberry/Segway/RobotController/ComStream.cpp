#include "ComStream.h"
#include <iostream>

ComStream::ComStream(ComPort* comPort) {
    _ComPort = comPort;
    _DataAvailable = false;
}

ComStream::~ComStream() {
}

bool ComStream::available() {
    if(!_DataAvailable) {
        int d = _ComPort->ReceiveChar();
        if(d < 0)
        {
            return false;
        }
        else
        {
            _DataRead = d;
            _DataAvailable = true;
            return true;
        }
    }
    else
    {
        return true;
    }
}

int ComStream::read() {
    if(available())
    {
       _DataAvailable = false;
       return _DataRead;
    }
    else
    {
        return -1;
    }
}

void ComStream::write(int data) {
    _ComPort->Send(data);
    std::cout << "Sent to Raspi:" << data << std::endl;
}

