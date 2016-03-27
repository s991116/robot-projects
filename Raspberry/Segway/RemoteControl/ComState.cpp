#include "ComState.h"
#include <ncurses.h>
#include "Convert.h"

ComState::ComState(SerialCommandProtocol* serialProtocol) {
    this->_SerialProtocol = serialProtocol;
}

State* ComState::View() {
  this->Print();
  return Control();
}

void ComState::Print() {
    clear();
    printw("*** ComSerial ***\n");
    printw("S - Send data\n");
    printw("R - Read data\n");
    printw("Q - Quit\n");
}

State* ComState::Control() {
    noecho();
    int c = getch();
    int data, id;
    switch (c) {
        case 'q':
            return ReturnState;
            break;
            
        case 's':
            id  = this->ReadInteger("Command id:");
            data = this->ReadInteger("Data to send:");
            _SerialProtocol->sendCommandAndData((unsigned char)id, (char16_t)data);
            break;

        case 'r':
            _SerialProtocol->handleResponse();
            data = _SerialProtocol->_CommunicationHandler->lastData;
            WriteMessage(Convert::IntToString(data).c_str());
            break;
    }
    return this;
}

ComState::~ComState() {   
}