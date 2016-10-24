#ifndef SERIALCONNECTORMOCK_H
#define	SERIALCONNECTORMOCK_H

#include "SerialComMock.h"

class SerialConnectorMock {
public:
    SerialConnectorMock();
    SerialCom* GetSerialCom1();
    SerialCom* GetSerialCom2();
    
    virtual ~SerialConnectorMock();
private:
    SerialComMock* _Com1;
    SerialComMock* _Com2;
   
};

#endif	/* SERIALCONNECTORMOCK_H */

