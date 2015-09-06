#include "CameraState.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <sstream>

CameraState::CameraState(CameraSensor* cameraSensor) {
    _CameraSensor = cameraSensor;
    _Position = new Position(0,0);
}

State* CameraState::View() {
    clear();
    printw("*** Camera ***\n");
    printw("P         - Take Picture\n");
    printw("F         - Facedetection\n");
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
            
        case 'f':
            cbreak();
            noecho();
            nodelay(stdscr, TRUE);
            scrollok(stdscr, TRUE);
            while (!kbhit()) {
                bool faceDetected = _CameraSensor->GetFacePosition(_Position);
            }
            echo();
            nodelay(stdscr, FALSE);
            scrollok(stdscr, FALSE);

            break;

    }
    return this;
}

int CameraState::kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

CameraState::~CameraState() {
}

