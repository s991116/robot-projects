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

void Servo::SetHorizontalPosition(short pos) {
    if(pos != _HorizontalPos)
    {
        _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL, pos);
        _HorizontalPos = pos;
    }
}

void Servo::SetVerticalPosition(short pos) {
    if(pos != _VerticalPos)
    {
      _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SERVO_VERTICAL, pos);
      _VerticalPos = pos;
    }
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
    SetVerticalPosition(pos);
}

void Servo::StepDown(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_VERTICAL);
    pos = pos + steps;
    SetVerticalPosition(pos);
}

void Servo::StepLeft(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos - steps;
    SetHorizontalPosition(pos);
}

void Servo::StepRight(int steps) {
    short pos = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos + steps;
    SetHorizontalPosition(pos);
}
 
void Servo::ToCenter() {
    SetVerticalPosition(90);
    SetHorizontalPosition(90);
}

Servo::~Servo() {
}