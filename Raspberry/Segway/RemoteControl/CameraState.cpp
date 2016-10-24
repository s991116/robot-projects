#include "CameraState.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Convert.h"

CameraState::CameraState(CameraSensor* cameraSensor) {
    _CameraSensor = cameraSensor;
    _Position = new Position();
    _LineDetectionPresentation = new LineDetectionPresentation(_CameraSensor, _Position);
    _PictureCount = 1;
}

State* CameraState::View() {
    clear();
    printw("*** Camera ***\n");
    printw("P         - Take Picture\n");
    printw("L         - Linedetection\n");
    printw("I         - Linedetection from picture\n");
    printw("Q         - Return\n");
    printw("\n");    
    printw("\n");

    noecho();
    int number;
    std::string filename;
    std::string lineInfo;
    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
        
        case 'p':            
            filename = "TakePicture_" + Convert::IntToString(_PictureCount) + ".jpg";
            _PictureCount++;
            _CameraSensor->TakePicture(filename.c_str());
            WriteMessage("Picture taken.");
            break;
            
        case 'i':
            number = this->ReadInteger("Picture no.:");
            filename = filename = "TakePicture_" + Convert::IntToString(number) + ".jpg";
            lineInfo = _CameraSensor->GetLine(filename)->ToString();
            this->WriteMessage(lineInfo);
            break;

        case 'l':
            LoopDisplayFunction(_LineDetectionPresentation);
            break;
    }
    return this;
}

CameraState::~CameraState() {
}