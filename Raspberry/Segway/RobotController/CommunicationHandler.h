#ifndef COMMUNICATIONHANDLER_H
#define	COMMUNICATIONHANDLER_H

#include "DataHandlerInterface.h"

class CommunicationHandler : public DataHandlerInterface {
public:
    CommunicationHandler();
    virtual ~CommunicationHandler();
    
    void HandleData(char commandId, char length, char data[]);
    void HandleData(char commandId, char length, short data[]);
    void HandleReply(char commandId, char length, char data[]);
    void HandleReply(char commandId, char length, short data[]);
    
    
    int lastCommandId;
    int lastData;
    
private:
    
};

#endif	/* COMMUNICATIONHANDLER_H */

