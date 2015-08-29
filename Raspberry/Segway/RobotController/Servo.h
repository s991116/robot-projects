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

    virtual ~Servo();
private:
    HardwareController* _HardwareController;
};

#endif	/* SERVO_H */

