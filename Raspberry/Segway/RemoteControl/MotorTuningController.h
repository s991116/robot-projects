#ifndef MOTORTUNINGCONTROLLER_H
#define	MOTORTUNINGCONTROLLER_H

#include "IMotorTuning.h"
#include "IMotor.h"

class MotorTuningController {
public:
    MotorTuningController(IMotorTuning* motorTuning, IMotor* motor);
    virtual ~MotorTuningController();
    void RunMeasure();
private:
    void SetMotorSpeed(short speed);
    IMotorTuning* _MotorTuning;
    IMotor* _Motor;
};

#endif	/* MOTORTUNINGCONTROLLER_H */

