#include "DataHandler.h"

DataHandler::DataHandler() {
    CommandIdReceived = 0;
}

void DataHandler::HandleData(char commandId, char length, char data[]) {
    CommandIdReceived = commandId;
}

void DataHandler::HandleData(char commandId, char length, short data[]) {
    CommandIdReceived = commandId;
}

void DataHandler::HandleReply(char commandId, char length, char data[]) {
    CommandIdReceived = commandId;
}

void DataHandler::HandleReply(char commandId, char length, short data[]) {
    CommandIdReceived = commandId;
}

DataHandler::~DataHandler() {
}

