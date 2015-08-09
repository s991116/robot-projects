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
    printw("O - Set angle offset\n");    
    printw("P - Set Gyro PID P-Factor\n");
    printw("I - Set Gyro PID I-Factor\n");
    printw("D - Set Gyro PID D-Factor\n");
    printw("G - Set Gyro PID Factor\n");
    printw("T - Enable/Disable Gyro-PID\n");
    printw("Q - Return\n");
    
    printw("Angle: ");
    printw(Convert::IntToString(_Gyro->GetAngle()).c_str());
    printw("\n");

    printw("Angle Offset: ");
    printw(Convert::IntToString(_Gyro->GetAngleOffset()).c_str());
    printw("\n");
    
    
    printw("Angle factor: ");
    printw(Convert::IntToString(_Gyro->GetAngleFactor()).c_str());
    printw("\n");
    
    printw("Angle Acc: ");
    printw(Convert::IntToString(_Gyro->GetAngleAccelration()).c_str());
    printw("\n");
    
    printw("Gyro P,I,D (incl. factor): ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_p()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_i()).c_str());
    printw(" , ");
    printw(Convert::IntToString(_Gyro->GetAnglePid_d()).c_str());
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
            number = ReadInteger("Set Angle factor:");
            _Gyro->SetAngleFactor(number);
            break;

        case 'o':
            number = ReadInteger("Set Angle offset:");
            _Gyro->SetAngleOffset(number);
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