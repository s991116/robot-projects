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
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Kp);
}

short Motor::GetLeftI() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Ki);
}

short Motor::GetLeftD() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_PID_Kd);
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
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Kp);
}

short Motor::GetRightI() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Ki);
}

short Motor::GetRightD() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_PID_Kd);
}

void Motor::SetMotorLeftSpeed(short speed) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorLeft_Speed, speed);
}

void Motor::SetMotorRightSpeed(short speed) {
    _HardwareController->SendCommand(MotorCommandType::Set_MotorRight_Speed, speed);
}

short Motor::GetMotorLeftSpeed() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_Speed);
}

short Motor::GetMotorRightSpeed() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_Speed);
}

short Motor::GetMotorLeftDistance() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorLeft_Distance);
}

short Motor::GetMotorRightDistance() {
    return _HardwareController->SendCommand(MotorCommandType::Get_MotorRight_Distance);
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

void  Motor::SetMotorSlackCount(short count) {
    _HardwareController->SendCommand(MotorCommandType::Set_Motor_Slack_Count, count);    
}

short Motor::GetMotorSlackCount(){
    return _HardwareController->SendCommand(MotorCommandType::Get_Motor_Slack_Count);    
}

void  Motor::SetMotorSlackPWMSpeed(short speed) {
    _HardwareController->SendCommand(MotorCommandType::Set_Motor_Slack_PWMSpeed, speed);    
}

short Motor::GetMotorSlackPWMSpeed(){
    return _HardwareController->SendCommand(MotorCommandType::Get_Motor_Slack_PWMSpeed);    
}

void  Motor::SetMotorSlackMode(short mode) {
    _HardwareController->SendCommand(MotorCommandType::Set_Motor_Slack_Mode, mode);    
}

short Motor::GetMotorSlackMode(){
    return _HardwareController->SendCommand(MotorCommandType::Get_Motor_Slack_Mode);    
}

void Motor::TestMotorSlack(short mode) {
    _HardwareController->SendCommand(MotorCommandType::Test_MotorSlack, mode);
    usleep(1000000); //Wait 1000 ms
}

Motor::~Motor() {
}