#include "SerialProtocol.h"

SerialCommandProtocol::SerialCommandProtocol(ComStream *serial, CommunicationHandler* communicationHandler) {
    _Serial = serial;
    _CommunicationHandler = communicationHandler;
}

/// <summary>
/// commandID 0-31
/// </summary>

void SerialCommandProtocol::sendCommandAndData(unsigned char commandID, unsigned char payload) {
    createAndSendCommand(commandID, COMMAND_DATA_BYTE_NO_REPLY);
    sendDataByte(payload);
}

/// <summary>
/// commandID 0-31
/// </summary>

void SerialCommandProtocol::sendCommandAndData(unsigned char commandID, char16_t payload) {
    createAndSendCommand(commandID, COMMAND_DATA_SHORT_NO_REPLY);
    sendDataShort(payload);
}

/// <summary>
/// commandID 0-31
/// </summary>

void SerialCommandProtocol::sendCommand(unsigned char commandID) {
    createAndSendCommand(commandID, COMMAND_NO_DATA_NO_REPLY);
}

char16_t SerialCommandProtocol::getShortData(unsigned char commandID) {
    createAndSendCommand(commandID, COMMAND_NO_DATA_SHORT_REPLY);
    char16_t response;
    while (!handleResponseAndReply(&response));
    return response;
}

unsigned char SerialCommandProtocol::getByteData(unsigned char commandID) {
    createAndSendCommand(commandID, COMMAND_NO_DATA_BYTE_REPLY);
    char16_t response;
    while (!handleResponseAndReply(&response));
    return response;
}

void SerialCommandProtocol::handleResponse() {
    char16_t *data;
    handleResponseAndReply(data);
}

bool SerialCommandProtocol::handleResponseAndReply(char16_t *data) {
    if (_Serial->available() == 0)
        return false;

    unsigned char response = _Serial->read();
    unsigned char responseType = (response & COMMAND_REPLY_FILTER);
    unsigned char responseCommandId = (response & COMMAND_ID_FILTER);
    switch (responseType) {
        case REPLY_BYTE:
            *data = getDataByte();
            return true;

        case REPLY_SHORT:
            *data = getDataShort();
            return true;

        case COMMAND_DATA_BYTE_NO_REPLY:
        {
            unsigned char responseDataByte = getDataByte();
            _CommunicationHandler->handleData(responseType, responseCommandId, responseDataByte);
            return false;
        }

        case COMMAND_DATA_SHORT_NO_REPLY:
        {
            char16_t responseDataShort = getDataShort();
            _CommunicationHandler->handleData(responseType, responseCommandId, responseDataShort);
            return false;
        }

        case COMMAND_NO_DATA_NO_REPLY:
        {
            _CommunicationHandler->handleCommand(responseCommandId);
            return false;
        }

        case COMMAND_NO_DATA_BYTE_REPLY:
        {
            unsigned char replyByte = _CommunicationHandler->handleReply(responseType, responseCommandId);
            createReplyAndSend(REPLY_BYTE, replyByte);
            return false;
        }

        case COMMAND_NO_DATA_SHORT_REPLY:
        {
            char16_t replyShort = _CommunicationHandler->handleReply(responseType, responseCommandId);
            createReplyAndSend(REPLY_SHORT, replyShort);
            return false;
        }
    }
    return false;
}

void SerialCommandProtocol::createReplyAndSend(unsigned char commandType, unsigned char reply) {
    createAndSendCommand(0, commandType);
    sendDataByte(reply);
}

void SerialCommandProtocol::createReplyAndSend(unsigned char commandType, char16_t reply) {
    createAndSendCommand(0, commandType);
    sendDataShort(reply);
}

void SerialCommandProtocol::createAndSendCommand(unsigned char commandID, unsigned char commandType) {
    unsigned char command = createCommand(commandID, commandType);
    sendByte(command);
}

unsigned char SerialCommandProtocol::createCommand(unsigned char commandID, unsigned char commandType) {
    return ((commandID & COMMAND_ID_FILTER) | commandType);
}

void SerialCommandProtocol::sendByte(unsigned char data) {
    _Serial->write(data);
}

unsigned char SerialCommandProtocol::waitGetByte() {
    while (_Serial->available() == 0);
    return _Serial->read();
}

char16_t SerialCommandProtocol::getDataShort() {
    char16_t high = getDataByte();
    char16_t low = getDataByte();
    char16_t result = ((high << 8) | low);
    return result;
}

void SerialCommandProtocol::sendDataShort(char16_t data) {
    unsigned char high = (data >> 8);
    unsigned char low = (data & 0xFF);
    sendDataByte(high);
    sendDataByte(low);
}

void SerialCommandProtocol::sendDataByte(unsigned char data) {
    unsigned char high = (data >> 4);
    unsigned char low = (data & 0x0F);
    _Serial->write(high);
    _Serial->write(low);
}

unsigned char SerialCommandProtocol::getDataByte() {
    unsigned char high = waitGetByte();
    unsigned char low = waitGetByte();
    unsigned char result = ((high << 4) | low);
    return result;
}

