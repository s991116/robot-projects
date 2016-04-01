#include "CameraState.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <sstream>

CameraState::CameraState(CameraSensor* cameraSensor) {
    _CameraSensor = cameraSensor;
    _Position = new Position();
    
    _FaceDetectionPresentation = new FaceDetectionPresentation(_CameraSensor, _Position);
    _LineDetectionPresentation = new LineDetectionPresentation(_CameraSensor, _Position);
}

State* CameraState::View() {
    clear();
    printw("*** Camera ***\n");
    printw("P         - Take Picture\n");
    printw("F         - Facedetection\n");
    printw("L         - Linedetection\n");
    printw("Q         - Return\n");
    printw("\n");    
    printw("\n");

    noecho();
    int number;
    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
        
        case 'p':
            _CameraSensor->TakePicture("TakePicture.jpg");
            WriteMessage("Picture taken.");
            break;

        case 'l':
            LoopDisplayFunction(_LineDetectionPresentation);
            break;

        case 'f':
            LoopDisplayFunction(_FaceDetectionPresentation);
            break;
    }
    return this;
}

CameraState::~CameraState() {
}