#include "Servo.h"
#include "CommandType.h"

Servo::Servo(MessageDataProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

short Servo::GetHorizontalPosition() {
    return _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
}

short Servo::GetVerticalPosition() {
    return _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_VERTICAL);
}

void Servo::SetHorizontalPosition(short pos) {
    if(pos != _HorizontalPos)
    {
        _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SERVO_HORIZONTAL, pos);
        _HorizontalPos = pos;
    }
}

void Servo::SetVerticalPosition(short pos) {
    if(pos != _VerticalPos)
    {
      _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SERVO_VERTICAL, pos);
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
    short pos = _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_VERTICAL);
    pos = pos - steps;
    SetVerticalPosition(pos);
}

void Servo::StepDown(int steps) {
    short pos = _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_VERTICAL);
    pos = pos + steps;
    SetVerticalPosition(pos);
}

void Servo::StepLeft(int steps) {
    short pos = _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos - steps;
    SetHorizontalPosition(pos);
}

void Servo::StepRight(int steps) {
    short pos = _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SERVO_HORIZONTAL);
    pos = pos + steps;
    SetHorizontalPosition(pos);
}
 
void Servo::ToCenter() {
    SetVerticalPosition(90);
    SetHorizontalPosition(90);
}

Servo::~Servo() {
}