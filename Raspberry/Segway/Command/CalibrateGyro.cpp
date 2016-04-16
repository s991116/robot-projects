#include "CalibrateGyro.h"

CalibrateGyro::CalibrateGyro(Navigate* navigate, Gyro* gyro) {
    _Navigate = navigate;
    _Gyro = gyro;
    
    SettingsInt["PID_P"] = &PID_P;
    SettingsInt["PID_I"] = &PID_I;
    SettingsInt["PID_D"] = &PID_D;
}

std::string CalibrateGyro::Execute(vector<int> input) {
    _Gyro->SetAnglePid_p(PID_P);
    _Gyro->SetAnglePid_i(PID_I);
    _Gyro->SetAnglePid_d(PID_D);
    return "Gyro PID settings written";
}

CalibrateGyro::~CalibrateGyro() {
}

