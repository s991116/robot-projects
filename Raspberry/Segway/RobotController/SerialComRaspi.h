#ifndef SERIALCOMRASPI_H
#define	SERIALCOMRASPI_H

#include "SerialCom.h"
#include "ComStream.h"

class SerialComRaspi : public SerialCom{
public:
    SerialComRaspi(ComStream* comStream);
    int DataAvailable();
    int PeekNextChar();
    int ReadNextChar();
    void WriteChar(int data);

    virtual ~SerialComRaspi();
private:
    ComStream* _ComStream;
};

#endif	/* SERIALCOMRASPI_H */

