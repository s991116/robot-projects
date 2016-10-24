#ifndef HANDLERMOCK_H
#define	HANDLERMOCK_H

#include "DataHandlerInterface.h"

class HandlerMock : public DataHandlerInterface {
public:
    HandlerMock();
    virtual ~HandlerMock();
    
    virtual void HandleData(char commandId, char length, char data[]);
    virtual void HandleData(char commandId, char length, short data[]);    
    virtual void HandleReply(char commandId, char length, char data[]);
    virtual void HandleReply(char commandId, char length, short data[]);
    
    int LastCommandReceived;
    char LastLengthReceived;
    char LastCharDataReceived[100];
    short LastShortDataReceived[100];
    
private:

};

#endif	/* HANDLERMOCK_H */

