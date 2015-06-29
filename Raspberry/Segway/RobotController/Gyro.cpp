#include "Gyro.h"

Gyro::Gyro(HardwareController* hardwareController) {
    _HardwareController = hardwareController;
}

short Gyro::GetAngle() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR,1);
}

void Gyro::SetAngleFactor(short factor) {
    _HardwareController->SendCommand(RobotCommandType::Set_Gyro_YPR_Factor,factor);
}

short Gyro::GetAngleFactor() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Factor,0);
}

short Gyro::GetAngleAccelration() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Gyro_YPR_Accelration,1);
}


Gyro::~Gyro() {
}

