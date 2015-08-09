#include "Gyro.h"

Gyro::Gyro(HardwareController* hardwareController) {
    _HardwareController = hardwareController;
}

short Gyro::GetAngle() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR, 1);
}

void Gyro::SetAngleFactor(short factor) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_YPR_Factor, factor);
}

short Gyro::GetAngleFactor() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Factor, 0);
}

void Gyro::SetAngleOffset(short offset) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_Angle_Offset, offset);
}

short Gyro::GetAngleOffset() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_Angle_Offset, 0);
}

short Gyro::GetAngleAccelration() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Accelration, 1);
}

short Gyro::GetAnglePid_p() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Kp, 0);
}

short Gyro::GetAnglePid_i() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Ki, 0);
}

short Gyro::GetAnglePid_d() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_PID_Kd, 0);
}

void Gyro::SetAnglePid_p(short p) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Kp, p);
}

void Gyro::SetAnglePid_i(short i) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_PID_Ki, i);
}

void Gyro::SetAnglePid_d(short d) {
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

