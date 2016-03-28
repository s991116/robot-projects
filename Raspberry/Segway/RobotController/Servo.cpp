#include "Servo.h"

Servo::Servo(SerialCommandProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

short Servo::GetHorizontalPosition() {
    return _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
}

short Servo::GetVerticalPosition() {
    return _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_VERTICAL);
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
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_VERTICAL);
    pos = pos - steps;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_VERTICAL, pos);
}

void Servo::StepDown(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_VERTICAL);
    pos = pos + steps;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_VERTICAL, pos);
}

void Servo::StepLeft(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos - steps;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL, pos);
}

void Servo::StepRight(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos + steps;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL, pos);
}
 
void Servo::ToCenter() {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_VERTICAL, 90);
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL, 90);
}

Servo::~Servo() {
}