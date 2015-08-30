#include "State.h"
#include <ncurses.h>
#include "Convert.h"

State::State() {
    this->Quit = false;
}

int State::ReadInteger() {
    return ReadInteger("");
}

int State::ReadInteger(std::string text) {
    printw(text.c_str());
    std::string result = this->ReadString();
    noecho();
    return Convert::StringToInt(result);
}

std::string State::ReadString() {
    return ReadString("");
}

void State::WriteMessage(std::string message) {
    cbreak();
    printw(message.c_str());
    getch();
}

std::string State::ReadString(std::string text) {
    printw(text.c_str());
    std::string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while (ch != '\n') {
        input.push_back(ch);
        ch = getch();
    }
    noecho();
    cbreak();

    return input;
}