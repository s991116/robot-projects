#include "GyroState.h"
#include <ncurses.h>
#include "Convert.h"

GyroState::GyroState(Gyro* gyro) {
    _Gyro = gyro;
}

State* GyroState::View() {
    clear();
    printw("*** Gyro tuning ***\n");
    printw("F - Set angle factor\n");
    printw("Q - Return\n");
    printw("Angle: ");
    printw(Convert::IntToString(_Gyro->GetAngle()).c_str());
    printw("\n");
    printw("Angle factor: ");
    printw(Convert::IntToString(_Gyro->GetAngleFactor()).c_str());
    printw("\n");
    printw("Angle Acc: ");
    printw(Convert::IntToString(_Gyro->GetAngleAccelration()).c_str());
    printw("\n");

    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
            
        case 'f':
            short number = ReadInteger("Set Gyro factor:");
            _Gyro->SetAngleFactor(number);
            break;

            break;
    }
    return this;
}

GyroState::~GyroState() {
}