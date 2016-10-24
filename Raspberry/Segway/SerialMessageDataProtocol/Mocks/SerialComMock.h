#ifndef SERIALCOMMOCK_H
#define	SERIALCOMMOCK_H

#include "SerialCom.h"

class SerialComMock : public SerialCom {
public:
    SerialComMock();
    void SetOppositeSerial(SerialComMock* oppositeSerial);

    virtual int DataAvailable();
    virtual int PeekNextChar();
    virtual int ReadNextChar();
    virtual void WriteChar(int data);

    void AppendDataToBuffer(int data);
        
    virtual ~SerialComMock();
private:
    SerialComMock* _OppositeSerial;
    int _BufferStartIndex;
    int _BufferEndIndex;
    char _Buffer[100];

};

#endif	/* SERIALCOMMOCK_H */

