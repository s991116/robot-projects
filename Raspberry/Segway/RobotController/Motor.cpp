#include "Motor.h"
#include "CommandType.h"

Motor::Motor(MessageDataProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

void Motor::SetLeftP(short p) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_P, p);
}

void Motor::SetLeftI(short i) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_I, i);
}

void Motor::SetLeftD(short d) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_D, d);
}

short Motor::GetLeftP() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_P);
} 

short Motor::GetLeftI() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_I);
}

short Motor::GetLeftD() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_A_D);
}

void Motor::SetRightP(short p) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_P, p);
}

void Motor::SetRightI(short i) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_I, i);
}

void Motor::SetRightD(short d) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_D, d);
}

short Motor::GetRightP() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_P);
}

short Motor::GetRightI() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_I);
}

short Motor::GetRightD() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_ENCODER_B_D);
}

Motor::~Motor() {
}