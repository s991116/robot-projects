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
    printw("M - Send Command\n");
    printw("S - Send data byte\n");
    printw("D - Send data short\n");
    printw("F - Read data byte from Command\n");
    printw("G - Read data short from Command\n");
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
            id = this->ReadInteger("Command id:");
            data = this->ReadInteger("Data to send:");
            _SerialProtocol->sendCommandAndData((unsigned char) id, (unsigned char) data);
            break;

        case 'd':
            id = this->ReadInteger("Command id:");
            data = this->ReadInteger("Data to send:");
            _SerialProtocol->sendCommandAndData((unsigned char) id, (char16_t) data);
            break;

        case 'f':
            id = this->ReadInteger("Command id:");
            data = _SerialProtocol->getByteData(id);
            WriteMessage(Convert::IntToString(data).c_str());
            break;

        case 'g':
            id = this->ReadInteger("Command id:");
            data = _SerialProtocol->getShortSignedData(id);
            WriteMessage(Convert::IntToString(data).c_str());
            break;

        case 'm':
            id = this->ReadInteger("Command id:");
            _SerialProtocol->sendCommand((unsigned char) id);
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