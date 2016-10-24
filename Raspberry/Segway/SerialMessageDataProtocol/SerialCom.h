#ifndef SERIALCOM_H
#define	SERIALCOM_H

class SerialCom{
public:
    virtual int DataAvailable() = 0;
    virtual int PeekNextChar() = 0;
    virtual int ReadNextChar() = 0;
    virtual void WriteChar(int data) = 0;
    
private:
    
};

#endif	/* SERIALCOM_H */

