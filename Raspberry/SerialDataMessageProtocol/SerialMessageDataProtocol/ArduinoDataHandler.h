#ifndef ARDUINODATAHANDLER_H
#define	ARDUINODATAHANDLER_H

#include "DataHandlerInterface.h"

class ArduinoDataHandler : public DataHandlerInterface {
public:
    ArduinoDataHandler(
            void (*handleDataChar)(char commandId, char length, char data[]), 
            void (*handleDataShort)(char commandId, char length, short data[]),
            void (*handleReplyChar)(char commandId, char length, char data[]),
            void (*handleReplyShort)(char commandId, char length, short data[]));
            
    virtual void HandleData(char commandId, char length, char data[]);
    virtual void HandleData(char commandId, char length, short data[]);
    virtual void HandleReply(char commandId, char length, char data[]);
    virtual void HandleReply(char commandId, char length, short data[]);
    
    virtual ~ArduinoDataHandler();
private:
    void (*_HandleDataChar)(char commandId, char length, char data[]);
    void (*_HandleDataShort)(char commandId, char length, short data[]);
    void (*_HandleReplyChar)(char commandId, char length, char data[]);
    void (*_HandleReplyShort)(char commandId, char length, short data[]);

};

#endif	/* ARDUINODATAHANDLER_H */

