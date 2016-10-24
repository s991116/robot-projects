#include "ArduinoDataHandler.h"

ArduinoDataHandler::ArduinoDataHandler(
            void (*handleDataChar)(char commandId, char length, char data[]), 
            void (*handleDataShort)(char commandId, char length, short data[]),
            void (*handleReplyChar)(char commandId, char length, char data[]),
            void (*handleReplyShort)(char commandId, char length, short data[])) {
    _HandleDataChar = handleDataChar;
    _HandleDataShort = handleDataShort;
    _HandleReplyChar = handleReplyChar;
    _HandleReplyShort = handleReplyShort;

}

void ArduinoDataHandler::HandleData(char commandId, char length, char data[]) {
    _HandleDataChar(commandId, length, data);
}

void ArduinoDataHandler::HandleData(char commandId, char length, short data[]) {
    _HandleDataShort(commandId, length, data);
}

void ArduinoDataHandler::HandleReply(char commandId, char length, char data[]) {
    _HandleReplyChar(commandId, length, data);
}

void ArduinoDataHandler::HandleReply(char commandId, char length, short data[]) {
    _HandleReplyShort(commandId, length, data);
}

ArduinoDataHandler::~ArduinoDataHandler() {
}