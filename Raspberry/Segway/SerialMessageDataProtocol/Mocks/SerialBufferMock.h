#ifndef SERIALBUFFERMOCK_H
#define	SERIALBUFFERMOCK_H

#include "SerialCom.h"

class SerialBufferMock : public SerialCom {
public:
    SerialBufferMock();
    virtual int DataAvailable();
    virtual int PeekNextChar();
    virtual int ReadNextChar();
    virtual void WriteChar(int data);
    
    char serialData[100];
    int  BufferIndexStart;
    int BufferIndexEnd;
    virtual ~SerialBufferMock();
private:

};

#endif	/* SERIALBUFFERMOCK_H */

