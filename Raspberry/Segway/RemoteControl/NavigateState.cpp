#include "NavigateState.h"
#include <ncurses.h>
#include "Convert.h"

NavigateState::NavigateState(Navigate* navigate, Distance* distance) {
    _Navigate = navigate;
    _Distance = distance;
    _TurnSpeed = 5;
    _Speed = 10;
}

NavigateState::~NavigateState() {
}

State* NavigateState::View() {
    clear();
    printw("*** Navigation ***\n");
    printw("Arrow-key - Forward, Left, Backwards, Right\n");
    printw("P, I, D   - PID-factor\n");    
    printw("L         - PID-limit\n"); 
    printw("O         - SpeedCorr-limit\n");
    printw("E         - Enable Segway\n");
    printw("R         - Disable Segway\n");
    printw("S         - Set Speed\n");
    printw("T         - Set turn speed\n");
    printw("U         - Reset Distance\n");    
    printw("Q         - Return\n");
    printw("\n");
    printw("Navigate PID: ");
    printw(Convert::IntToString(_Navigate->GetPID_P()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Navigate->GetPID_I()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Navigate->GetPID_D()).c_str());
    printw("\n");
    printw("Speed Corr limit: ");
    printw(Convert::IntToString(_Navigate->GetSpeedCorrLimit()).c_str());
    printw("\n");
    printw("Speed PID limit: ");
    printw(Convert::IntToString(_Navigate->GetPIDLimit()).c_str());
    printw("\n");

    printw("Speed offset: ");
    printw(Convert::IntToString(_Speed).c_str());
    printw("\n");
    printw("TurnSpeed offset: ");
    printw(Convert::IntToString(_TurnSpeed).c_str());
    printw("\n");
    printw("Distance: ");
    printw(Convert::IntToString(_Distance->GetDistance()).c_str());
    printw("\n");

    noecho();
    int number;
    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
        
        case 's':
            _Speed = ReadInteger("Set speed:");
            break;
            
        case 't':
            _TurnSpeed = ReadInteger("Set turn speed:");
            break;

        case 'e':
            _Navigate->EnableSegway();
            break;

        case 'r':
            _Navigate->DisableSegway();
            break;

        case KEY_UP:
            _Navigate->ForwardSpeed(_Speed);
            break;

        case KEY_DOWN:
            _Navigate->ForwardSpeed(-_Speed);
            break;

        case KEY_LEFT:
            _Navigate->TurnSpeed(_TurnSpeed);
            break;

        case KEY_RIGHT:
            _Navigate->TurnSpeed(-_TurnSpeed);
            break;

        case 'p':
            number = ReadInteger("Set P-correction:");
            _Navigate->SetPID_P(number);
            break;

        case 'i':
            number = ReadInteger("Set I-correction:");
            _Navigate->SetPID_I(number);
            break;

        case 'd':
            number = ReadInteger("Set D-correction:");
            _Navigate->SetPID_D(number);
            break;            

        case 'l':
            number = ReadInteger("Set PID-Limit:");
            _Navigate->SetPIDLimit(number);
            break;            
            
        case 'o':
            number = ReadInteger("Set SpeedCorr-Limit:");
            _Navigate->SetSpeedCorrLimit(number);
            break;            
            
        case 'u':
            _Distance->ResetDistance();
            break;                    

        default:
            _Navigate->TurnSpeed(0);
            _Navigate->ForwardSpeed(0);
            break;
    }
    return this;
}

std::string NavigateState::PrintDirection(DirectionEnum dir) {
    switch (dir) {
        case DirectionEnum::Forward:
            return "Forward";
        case DirectionEnum::Backwards:
            return "Backwards";
        case DirectionEnum::Left:
            return "Left";
        case DirectionEnum::Right:
            return "Right";
        case DirectionEnum::Stop:
            return "Stopped";
    }
    return "Unknown";
}