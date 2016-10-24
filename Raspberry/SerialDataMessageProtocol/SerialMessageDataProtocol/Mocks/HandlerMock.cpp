#include "HandlerMock.h"

HandlerMock::HandlerMock() {
}

void HandlerMock::HandleData(char commandId, char length, char data[]) {
    LastCommandReceived = commandId;
    LastLengthReceived = length;
    for(int i = 0; i< length; i++)
    {
        LastCharDataReceived[i] = data[i];
    }
}

void HandlerMock::HandleData(char commandId, char length, short data[]) {
    LastCommandReceived = commandId;
    LastLengthReceived = length;
    for(int i = 0; i< length; i++)
    {
        LastShortDataReceived[i] = data[i];
    }
}

void HandlerMock::HandleReply(char commandId, char length, char data[]) {
    LastCommandReceived = commandId;
    LastLengthReceived = length;
    
    for(int i = 0; i< length; i++)
    {
        LastCharDataReceived[i] = data[i];
    }    
}
void HandlerMock::HandleReply(char commandId, char length, short data[]) {
    LastCommandReceived = commandId;
    LastLengthReceived = length;
    
    for(int i = 0; i< length; i++)
    {
        LastShortDataReceived[i] = data[i];
    }    
}


HandlerMock::~HandlerMock() {
}