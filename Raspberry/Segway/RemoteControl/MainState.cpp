#include "MainState.h"
#include <ncurses.h>

MainState::MainState(State* motorState, State* gyroState, State* servoState, State* cameraState, State* comState, State* navigateState) {
    _MotorState = motorState;
    _MotorState->ReturnState = this;

    _GyroState = gyroState;
    _GyroState->ReturnState = this;

    _ServoState = servoState;
    _ServoState->ReturnState = this;    
    
    _CameraState = cameraState;
    _CameraState->ReturnState = this;
    
    _ComState = comState;
    _ComState->ReturnState = this;
    
    _NavigateState = navigateState;
    _NavigateState->ReturnState = this;
    
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
    printw("N - Navigate\n");
    printw("M - Motor tunning\n");
    printw("G - Gyro tunning\n");
    printw("S - Servo tunning\n");    
    printw("C - Camera\n"); 
    printw("O . comSerial\n");
    printw("Q - Quit\n");
}

State* MainState::Control() {
    noecho();
    int c = getch();
    
    switch (c) {
        case 'q':
            return ReturnState;
            break;
 
        case 'n':
            return _NavigateState;
            break;
            
        case 'g':
            return _GyroState;
            break;
            
        case 'm':
            return _MotorState;
            break;

        case 's':
            return _ServoState;
            break;

        case 'c':
            return _CameraState;
            break;

        case 'o':
            return _ComState;
            break;            
    }
    return this;
}