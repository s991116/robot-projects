#include "MainState.h"
#include <ncurses.h>

MainState::MainState(State* motorState) {
    _MotorState = motorState;
    _MotorState->ReturnState = this;
}

MainState::~MainState() {
}

State* MainState::View() {
    this->Print();
    return Control();
}

void MainState::Print() {
    clear();
    printw("*** Segway Control program ***\n");
    printw("M - Motor tunning\n");
    printw("Q - Quit\n");
}

State* MainState::Control() {
    noecho();
    int c = getch();
    
    switch (c) {
        case 'q':
            return this->ReturnState;
            break;
            
        case 'm':
            return _MotorState;
    }
    return this;
}