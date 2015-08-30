#include "MainState.h"
#include <ncurses.h>

MainState::MainState(State* motorState, State* gyroState, State* servoState, State* cameraState) {
    _MotorState = motorState;
    _MotorState->ReturnState = this;

    _GyroState = gyroState;
    _GyroState->ReturnState = this;

    _ServoState = servoState;
    _ServoState->ReturnState = this;    
    
    _CameraState = cameraState;
    _CameraState->ReturnState = this;
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
    printw("S - Servo tunning\n");    
    printw("C - Camera\n");        
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

        case 's':
            return _ServoState;
            break;

        case 'c':
            return _CameraState;
            break;
    }
    return this;
}