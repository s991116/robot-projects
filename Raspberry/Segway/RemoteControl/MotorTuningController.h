#ifndef MOTORTUNINGCONTROLLER_H
#define	MOTORTUNINGCONTROLLER_H

#include "IMotorTuning.h"
#include "IMotor.h"
#include <string>

class MotorTuningController {
public:
    MotorTuningController(IMotorTuning* motorTuning, IMotor* motor);
    virtual ~MotorTuningController();
    void RunMeasure();
    void SaveMeasureToFile(std::string filename);
private:
    void SetMotorSpeed(short speed);
    IMotorTuning* _MotorTuning;
    IMotor* _Motor;
};

#endif	/* MOTORTUNINGCONTROLLER_H */

