#ifndef SERVO_H
#define	SERVO_H

#include "SerialProtocol.h"

class Servo {
public:
    Servo(SerialCommandProtocol* serialProtocol);

    short GetHorizontalPosition();
    short GetVerticalPosition();
    void SetHorizontalPosition(short pos);
    void SetVerticalPosition(short pos);


    void StepUp();
    void StepDown();
    void StepLeft();
    void StepRight();

    void StepUp(int steps);
    void StepDown(int steps);
    void StepLeft(int steps);
    void StepRight(int steps);
    void ToCenter();

    virtual ~Servo();
private:
    SerialCommandProtocol* _SerialProtocol;
    short _VerticalPos;
    short _HorizontalPos;
};

#endif	/* SERVO_H */

