#include "GyroState.h"
#include <ncurses.h>
#include "Convert.h"

GyroState::GyroState(Gyro* gyro) {
    _Gyro = gyro;
}

State* GyroState::View() {
    clear();
    printw("*** Gyro tuning ***\n");
    printw("F - Set angel factor\n");
    printw("P - Set Gyro PID P-Factor\n");
    printw("I - Set Gyro PID I-Factor\n");
    printw("D - Set Gyro PID D-Factor\n");
    printw("G - Set Gyro PID Factor\n");
    printw("T - Enable/Disable Gyro-PID\n");
    printw("Q - Return\n");
    
    printw("Angel: ");
    printw(Convert::IntToString(_Gyro->GetAngel()).c_str());
    printw("\n");
    
    printw("Angel factor: ");
    printw(Convert::IntToString(_Gyro->GetAngelFactor()).c_str());
    printw("\n");
    
    printw("Angel Acc: ");
    printw(Convert::IntToString(_Gyro->GetAngelAccelration()).c_str());
    printw("\n");
    
    printw("Gyro P,I,D (incl. factor): ");
    printw(Convert::IntToString(_Gyro->GetAngelPid_p()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAngelPid_i()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAngelPid_d()).c_str());
    printw("\n");

    printw("Gyro PID Factor: ");
    printw(Convert::IntToString(_Gyro->GetGyroPidFactor()).c_str());
    printw("\n");

    if(_Gyro->GetPidState() == 1)
      printw("Gyro PID Enabled");
    else
      printw("Gyro PID Disabled");
    printw("\n");

    short number;
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;
            
        case 'f':
            number = ReadInteger("Set Angel factor:");
            _Gyro->SetAngelFactor(number);
            break;
            
        case 'p':
            number = ReadInteger("Set Gyro PID P-factor:");
            _Gyro->SetAngelPid_p(number);
            break;
            
        case 'i':
            number = ReadInteger("Set Gyro PID I-factor:");
            _Gyro->SetAngelPid_i(number);
            break;
            
        case 'd':
            number = ReadInteger("Set Gyro PID D-factor:");
            _Gyro->SetAngelPid_d(number);
            break;
            
        case 'g':
            number = ReadInteger("Set Gyro PID factor:");
            _Gyro->SetGyroPidFactor(number);
            break;
            
        case 't':
            bool state = _Gyro->GetPidState();
            state = !state;
            _Gyro->SetPidState(state);
            break;
    }
    return this;
}

GyroState::~GyroState() {
}