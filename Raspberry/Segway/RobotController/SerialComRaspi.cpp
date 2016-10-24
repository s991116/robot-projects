#include "SerialComRaspi.h"

SerialComRaspi::SerialComRaspi(ComStream* comStream) {
    _ComStream = comStream;
}

int SerialComRaspi::DataAvailable() {
    return 0;
}

int SerialComRaspi::PeekNextChar() {
    return 0;
}

int SerialComRaspi::ReadNextChar() {
    return 0;
}

void SerialComRaspi::WriteChar(int data) {
    
}

SerialComRaspi::~SerialComRaspi() {
}

