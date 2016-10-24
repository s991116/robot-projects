#ifndef MESSAGEDATAPROTOCOL_H
#define	MESSAGEDATAPROTOCOL_H

#include "DataPackets.h"
#include "DataHandlerInterface.h"

class MessageDataProtocol {
public:
    MessageDataProtocol(DataPackets* dataPackets, DataHandlerInterface* dataHandler); 
    void Update();
    void SendData(char commandId, char length, char data[]);
    void SendData(char commandId, short data);
    void SendData(char commandId, char length, short data[]);
    void SendData(char commandId, char data);    
    void SendData(char commandId, bool data);
    
    void RequestData(char commandId, char length, char data[]);
    void RequestData(char commandId, char length, short data[]);

    char RequestCharData(char commandId);
    short RequestShortData(char commandId);
        
    virtual ~MessageDataProtocol();
private:
    DataPackets* _DataPackets;
    DataHandlerInterface* _DataHandler;
    char _ReplyDataChar[7];
    short _ReplyDataShort[7];
    bool _ReplyReceived;
};

#endif	/* MESSAGEDATAPROTOCOL_H */