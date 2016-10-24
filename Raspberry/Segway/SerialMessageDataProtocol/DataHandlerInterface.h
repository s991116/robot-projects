
#ifndef DATAHANDLERINTERFACE_H
#define	DATAHANDLERINTERFACE_H

class DataHandlerInterface{
public:
    DataHandlerInterface() {};
    virtual void HandleData(char commandId, char length, char data[]) = 0;
    virtual void HandleData(char commandId, char length, short data[]) = 0;
    virtual void HandleReply(char commandId, char length, char data[]) = 0;
    virtual void HandleReply(char commandId, char length, short data[]) = 0;
private:

};


#endif	/* DATAHANDLERINTERFACE_H */

