#ifndef HEAD_CONTROL
#define HEAD_CONTROL

#include <Arduino.h>
#include <Servo.h>

class HeadControl {
    public:
        HeadControl(Servo *verticalServo, Servo *horizontalServo);
        void Initialize();
        void SetHorizontalPosition(byte position);
        void SetVerticalPosition(byte position);
        byte GetHorizontalPosition();
        byte GetVerticalPosition();

    private:
        Servo* _verticalServo;
        Servo* _horizontalServo;
        byte _verticalPosition;
        byte _horizontalPosition;

        byte LimitPosition(byte position, byte minPositon, byte maxPosition);

        byte _horizontalLimitMin = 70;
        byte _horizontalCenter = 110;
        byte _horizontalLimitMax= 150;
        byte _verticalLimitMin = 60;
        byte _verticalCenter = 140;
        byte _verticalLimitMax = 170;
};
#endif