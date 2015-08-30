#include "Servo.h"

Servo::Servo(HardwareController* hardwareController) {
    _HardwareController = hardwareController;
}

short Servo::GetHorizontalPosition() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Horizontal_Servo_Position);
}

short Servo::GetVerticalPosition() {
    return _HardwareController->SendCommand(RobotCommandType::Get_Vertical_Servo_Position);
}

void Servo::StepUp() {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Vertical_Servo_Position);
    pos = pos - 1;
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position, pos);
}

void Servo::StepDown() {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Vertical_Servo_Position);
    pos = pos + 1;
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position, pos);
}

void Servo::StepLeft() {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Horizontal_Servo_Position);
    pos = pos - 1;
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, pos);
}

void Servo::StepRight() {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Horizontal_Servo_Position);
    pos = pos + 1;
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, pos);
}

void Servo::ToCenter() {
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, 90);
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position,   90);
}

Servo::~Servo() {
}

