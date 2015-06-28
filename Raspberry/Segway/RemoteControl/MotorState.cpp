#include "MotorState.h"
#include <ncurses.h>
#include "Motor.h"
#include "Convert.h"

MotorState::MotorState(Motor* motor, MotorTuningController* motorTuningController) {
    _Motor = motor;
    _MotorTuningController = motorTuningController;
}

State* MotorState::View() {
    clear();
    printw("*** Motor tunning ***\n");
    printw("Arrow-key - Forward, Left, Backwards, Right\n");
    printw("F         - Fixed speed\n");
    printw("P, I, D   - PID-factor\n");
    printw("T         - Test-tuning\n");
    printw("Q         - Return\n");
    printw("\n");
    printw("Direction:");
    printw(PrintDirection(_Motor->GetDirection()).c_str());
    printw("\n");
    printw("Speed (Left, Right): ");
    printw(Convert::IntToString(_Motor->GetMotorLeftSpeed()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Motor->GetMotorRightSpeed()).c_str());
    printw("\n");
    printw("PID correction (Left): ");
    printw(Convert::IntToString(_Motor->GetLeftP()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Motor->GetLeftI()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Motor->GetLeftD()).c_str());
    printw("\n");
    printw("PID correction (Right): ");
    printw(Convert::IntToString(_Motor->GetRightP()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Motor->GetRightI()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Motor->GetRightD()).c_str());
    printw("\n");

    noecho();
    int number;
    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            _Motor->SetDirection(DirectionEnum::Stop);
            return this->ReturnState;
            break;

        case KEY_UP:
            _Motor->SetDirection(DirectionEnum::Forward);
            break;

        case KEY_DOWN:
            _Motor->SetDirection(DirectionEnum::Backwards);
            break;

        case KEY_LEFT:
            _Motor->SetDirection(DirectionEnum::Left);
            break;

        case KEY_RIGHT:

            _Motor->SetDirection(DirectionEnum::Right);
            break;

        case 'f':
            number = ReadInteger("Set speed:");
            _Motor->SetMotorLeftSpeed(number);
            _Motor->SetMotorRightSpeed(number);
            break;

        case 'p':
            number = ReadInteger("Set P-correction:");
            _Motor->SetLeftP(number);
            _Motor->SetRightP(number);
            break;

        case 'i':
            number = ReadInteger("Set I-correction:");
            _Motor->SetLeftI(number);
            _Motor->SetRightI(number);
            break;

        case 'd':
            number = ReadInteger("Set D-correction:");
            _Motor->SetLeftD(number);
            _Motor->SetRightD(number);
            break;
            
        case 't':
            printw("Tuning running...\n");
            _MotorTuningController->RunMeasure();
            printw("Save result to file...\n");
            _MotorTuningController->SaveMeasureToFile("Logfile.txt");
            break;

        default:
            _Motor->SetDirection(DirectionEnum::Stop);

    }
    return this;
}

std::string MotorState::PrintDirection(DirectionEnum dir) {
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

MotorState::~MotorState() {
}