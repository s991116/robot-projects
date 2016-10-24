#ifdef ARDUINO

#include "ArduinoSerial.h"

ArduinoSerial::ArduinoSerial(Stream* stream) {
    _Stream = stream;
}

int ArduinoSerial::DataAvailable() {
    return _Stream->available();
}

int ArduinoSerial::PeekNextChar() {
    return _Stream->peek();
}

int ArduinoSerial::ReadNextChar() {
    return _Stream->read();    
}

void ArduinoSerial::WriteChar(int data) {
    _Stream->write(data);
}

ArduinoSerial::~ArduinoSerial() {
}

#endif //ARDUINO