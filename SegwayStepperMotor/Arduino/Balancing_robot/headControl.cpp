#include "headControl.h"
#include "PinSetup.h"

HeadControl::HeadControl(Servo *verticalServo, Servo *horizontalServo) : _verticalServo(verticalServo) , _horizontalServo( horizontalServo) {
}

void HeadControl::Initialize() {
    _verticalServo->attach(PIN_SERVO_1);
    _horizontalServo->attach(PIN_SERVO_2);

    SetHorizontalPosition(_horizontalCenter);
    SetVerticalPosition(_verticalCenter);
}

void HeadControl::SetHorizontalPosition(byte position) {
    _horizontalPosition =HeadControl::LimitPosition(position, _horizontalLimitMin, _horizontalLimitMax);
    _horizontalServo->write(_horizontalPosition);
}

void HeadControl::SetVerticalPosition(byte position) {
    _verticalPosition = HeadControl::LimitPosition(position, _verticalLimitMin, _verticalLimitMax);
    _verticalServo->write(_verticalPosition);
}

byte HeadControl::GetHorizontalPosition() {
    return _horizontalPosition;
}

byte HeadControl::GetVerticalPosition() {
    return _verticalPosition;
}

byte HeadControl::LimitPosition(byte position, byte minPosition, byte maxPosition) {
    return max(minPosition, min(maxPosition, position));
}