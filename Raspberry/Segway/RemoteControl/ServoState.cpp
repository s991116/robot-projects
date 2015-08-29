#include "ServoState.h"
#include <ncurses.h>
#include "Servo.h"
#include "Convert.h"

ServoState::ServoState(Servo* servo) {
    _Servo = servo;
}

State* ServoState::View() {
    clear();
    printw("*** Servo tunning ***\n");
    printw("Arrow-key - Forward, Left, Backwards, Right\n");
    printw("Q         - Return\n");
    printw("\n");
    printw("Position Horizontal: ");
    printw(Convert::IntToString(_Servo->GetHorizontalPosition()).c_str());
    printw(" , Position Vertical: ");
    printw(Convert::IntToString(_Servo->GetVerticalPosition()).c_str());
    
    printw("\n");

    noecho();
    int number;
    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;

        case KEY_UP:
            _Servo->StepUp();
            break;

        case KEY_DOWN:
            _Servo->StepDown();
            break;

        case KEY_LEFT:
            _Servo->StepLeft();
            break;

        case KEY_RIGHT:
            _Servo->StepRight();
            break;
    }
    return this;
}

ServoState::~ServoState() {
}