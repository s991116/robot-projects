#include "MainState.h"
#include <ncurses.h>

MainState::MainState(State* motorState, State* gyroState) {
    _MotorState = motorState;
    _MotorState->ReturnState = this;

    _GyroState = gyroState;
    _GyroState->ReturnState = this;
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
    printw("G - Gyro tunning\n");
    printw("Q - Quit\n");
}

State* MainState::Control() {
    noecho();
    int c = getch();
    
    switch (c) {
        case 'q':
            return ReturnState;
            break;
            
        case 'g':
            return _GyroState;
            break;
            
        case 'm':
            return _MotorState;
            break;
    }
    return this;
}