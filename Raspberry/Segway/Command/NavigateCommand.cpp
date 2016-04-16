#include "NavigateCommand.h"

NavigateCommand::NavigateCommand(Navigate* navigate) {
    _Navigate = navigate;
    this->SettingsInt["PID_P"] = &_PID_P;
    this->SettingsInt["PID_I"] = &_PID_I;
    this->SettingsInt["PID_D"] = &_PID_D;
    this->SettingsInt["PID_LIMIT"] = &_PIDLimit;
    this->SettingsInt["SPEED_CORR_LIMIT"] = &_SpeedCorrLimit;

}

std::string NavigateCommand::Execute(vector<int> input) {
    _Navigate->SetPID_P(_PID_P);
    _Navigate->SetPID_I(_PID_I);
    _Navigate->SetPID_D(_PID_D);

    _Navigate->SetPIDLimit(_PIDLimit);
    _Navigate->SetSpeedCorrLimit(_SpeedCorrLimit);
    return "Navigation updated";
}

NavigateCommand::~NavigateCommand() {
}

