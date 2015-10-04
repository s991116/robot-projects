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
    StepUp(1);
}

void Servo::StepDown() {
    StepDown(1);
}

void Servo::StepLeft() {
    StepLeft(1);
}

void Servo::StepRight() {
    StepRight(1);
}

void Servo::StepUp(int steps) {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Vertical_Servo_Position);
    pos = pos - steps;
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position, pos);
}

void Servo::StepDown(int steps) {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Vertical_Servo_Position);
    pos = pos + steps;
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position, pos);
}

void Servo::StepLeft(int steps) {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Horizontal_Servo_Position);
    pos = pos - steps;
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, pos);
}

void Servo::StepRight(int steps) {
    short pos = _HardwareController->SendCommand(RobotCommandType::Get_Horizontal_Servo_Position);
    pos = pos + steps;
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, pos);
}
 
void Servo::ToCenter() {
    _HardwareController->SendCommand(RobotCommandType::Set_Horizontal_Servo_Position, 90);
    _HardwareController->SendCommand(RobotCommandType::Set_Vertical_Servo_Position,   90);
}

Servo::~Servo() {
}

