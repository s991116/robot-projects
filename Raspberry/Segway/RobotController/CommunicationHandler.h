#ifndef COMMUNICATIONHANDLER_H
#define	COMMUNICATIONHANDLER_H

class CommunicationHandler {
public:
    CommunicationHandler();
    virtual ~CommunicationHandler();
    
    void handleCommand(unsigned char commandId);
    void handleData(unsigned char responseType, unsigned char commandId, char16_t data);
    char16_t handleReply(unsigned char responseType, unsigned char commandId);
    
    int lastCommandId;
    int lastData;
    
private:
    
};

#endif	/* COMMUNICATIONHANDLER_H */

