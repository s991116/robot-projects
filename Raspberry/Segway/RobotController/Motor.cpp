#include "Motor.h"

Motor::Motor(HardwareController* hardwareController) {
    _HardwareController = hardwareController;
    _Direction = DirectionEnum::Stop;
}

void Motor::SetLeftP(short p) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorLeft_PID_Kp, p);
}

void Motor::SetLeftI(short i) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorLeft_PID_Ki, i);
}

void Motor::SetLeftD(short d) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorLeft_PID_Kd, d);
}

short Motor::GetLeftP() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Kp, 0);
}

short Motor::GetLeftI() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Ki, 0);
}

short Motor::GetLeftD() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Kd, 0);
}

void Motor::SetRightP(short p) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorRight_PID_Kp, p);
}

void Motor::SetRightI(short i) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorRight_PID_Ki, i);
}

void Motor::SetRightD(short d) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorRight_PID_Kd, d);
}

short Motor::GetRightP() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Kp, 0);
}

short Motor::GetRightI() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Ki, 0);
}

short Motor::GetRightD() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Kd, 0);
}

void Motor::SetMotorLeftSpeed(short speed) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorLeft_Speed, speed);
}

void Motor::SetMotorRightSpeed(short speed) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorRight_Speed, speed);
}

short Motor::GetMotorLeftSpeed() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_Speed, 0);
}

short Motor::GetMotorRightSpeed() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_Speed, 0);
}

void Motor::SetDirection(DirectionEnum direction) {
    _Direction = direction;
    short speed = 100;
    
    switch(direction)
    {
        case DirectionEnum::Stop:
            SetMotorLeftSpeed(0);
            SetMotorRightSpeed(0);
            _HardwareController->SendCommand(MotorCommandType::Set_Motor_Enabled, false);
            _HardwareController->SendCommand(MotorCommandType::Set_Motor_Enabled, true);            
            break;

        case DirectionEnum::Left:
            SetMotorLeftSpeed(speed);
            SetMotorRightSpeed(0);
            break;

        case DirectionEnum::Right:
            SetMotorLeftSpeed(0);
            SetMotorRightSpeed(speed);
            break;

        case DirectionEnum::Forward:
            SetMotorLeftSpeed(speed);
            SetMotorRightSpeed(speed);
            break;

        case DirectionEnum::Backwards:
            SetMotorLeftSpeed(-speed);
            SetMotorRightSpeed(-speed);
            break;
    }
}

DirectionEnum Motor::GetDirection() {
    return _Direction;
}

void Motor::SetMotorEnabled(bool state) {
    _HardwareController->SendCommand(MotorCommandType::Set_Motor_Enabled, state);
}

void  Motor::SetMotorSlackOffset(short offset) {
    _HardwareController->SendCommand(MotorCommandType::Set_Motor_Slack, offset);    
}

short Motor::GetMotorSlackOffset(){
    return _HardwareController->SendCommand(MotorCommandType::Get_Motor_Slack, 0);    
}

Motor::~Motor() {
}