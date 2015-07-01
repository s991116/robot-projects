#include "Gyro.h"

Gyro::Gyro(HardwareController* hardwareController) {
    _HardwareController = hardwareController;
}

short Gyro::GetAngel() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR, 1);
}

void Gyro::SetAngelFactor(short factor) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_YPR_Factor, factor);
}

short Gyro::GetAngelFactor() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Factor, 0);
}

short Gyro::GetAngelAccelration() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Accelration, 1);
}

short Gyro::GetAngelPid_p() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Kp, 0);
}

short Gyro::GetAngelPid_i() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Ki, 0);
}

short Gyro::GetAngelPid_d() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Kd, 0);
}

void Gyro::SetAngelPid_p(short p) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Kp, p);
}

void Gyro::SetAngelPid_i(short i) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Ki, i);
}

void Gyro::SetAngelPid_d(short d) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Kd, d);
}

void Gyro::SetGyroPidFactor(short factor) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Factor, factor);
}

short Gyro::GetGyroPidFactor() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Factor, 0);
}

void Gyro::SetPidState(short state) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_State, state);
}

short Gyro::GetPidState() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_State, 0);
}

Gyro::~Gyro() {
}

