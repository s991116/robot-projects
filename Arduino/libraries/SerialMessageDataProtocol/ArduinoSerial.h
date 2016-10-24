#ifdef ARDUINO

#ifndef ARDUINOSERIAL_H
#define	ARDUINOSERIAL_H

#include <Stream.h>
#include "SerialCom.h"

class ArduinoSerial : public SerialCom{
public:
    ArduinoSerial(Stream* stream);
    virtual int DataAvailable();
    virtual int PeekNextChar();
    virtual int ReadNextChar();
    virtual void WriteChar(int data);
    virtual ~ArduinoSerial();
private:
    Stream* _Stream;
};


#endif	/* ARDUINOSERIAL_H */

#endif ARDUINO
