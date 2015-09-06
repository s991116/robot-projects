#ifndef SERVO_H
#define	SERVO_H

#include "HardwareController.h"

class Servo {
public:
    Servo(HardwareController* hardwareController);

    short GetHorizontalPosition();
    short GetVerticalPosition();

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
    HardwareController* _HardwareController;
};

#endif	/* SERVO_H */

