#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler() {
    lastCommandId = -1;
    lastData = -1;
}

CommunicationHandler::~CommunicationHandler() {
}

void CommunicationHandler::HandleData(char commandId, char length, char data[]) {
    
}

void CommunicationHandler::HandleData(char commandId, char length, short data[]) {
    
}

void CommunicationHandler::HandleReply(char commandId, char length, char data[]) {
    
}

void CommunicationHandler::HandleReply(char commandId, char length, short data[]) {
    
}    

/*
void CommunicationHandler::handleCommand(unsigned char commandId) {
    this->lastCommandId = commandId;
}

void CommunicationHandler::handleData(unsigned char responseType, unsigned char commandId, char16_t data) {
    this->lastCommandId = commandId;
    this->lastData = data;
}

char16_t CommunicationHandler::handleReply(unsigned char responseType, unsigned char commandId) {
    return 0;
}
*/