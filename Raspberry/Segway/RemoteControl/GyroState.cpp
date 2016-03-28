#include "GyroState.h"
#include <ncurses.h>
#include "Convert.h"

GyroState::GyroState(Gyro* gyro) {
    _Gyro = gyro;
}

State* GyroState::View() {
    clear();
    printw("*** Gyro tuning ***\n");
    printw("P - Set Gyro PID P-Factor\n");
    printw("I - Set Gyro PID I-Factor\n");
    printw("D - Set Gyro PID D-Factor\n");
    printw("Q - Return\n");
    
    printw("Angle: ");
    printw(Convert::IntToString(_Gyro->GetAngle()).c_str());
    printw("\n");
    
    printw("Gyro P,I,D (incl. factor): ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_p()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_i()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_d()).c_str());
    printw("\n");

    short number;
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
            
        case 'p':
            number = ReadInteger("Set Gyro PID P-factor:");
            _Gyro->SetAnglePid_p(number);
            break;
            
        case 'i':
            number = ReadInteger("Set Gyro PID I-factor:");
            _Gyro->SetAnglePid_i(number);
            break;
            
        case 'd':
            number = ReadInteger("Set Gyro PID D-factor:");
            _Gyro->SetAnglePid_d(number);
            break;            
    }
    return this;
}

GyroState::~GyroState() {
}