#ifndef DATAHANDLER_H
#define	DATAHANDLER_H

#include "DataHandlerInterface.h"

class DataHandler : public DataHandlerInterface{
public:
    DataHandler();
    virtual void HandleData(char commandId, char length, char data[]);
    virtual void HandleData(char commandId, char length, short data[]);
    virtual void HandleReply(char commandId, char length, char data[]);
    virtual void HandleReply(char commandId, char length, short data[]);
    
    virtual ~DataHandler();
    int LastCamandReceived;
    int CommandIdReceived;
private:

};

#endif	/* DATAHANDLER_H */

