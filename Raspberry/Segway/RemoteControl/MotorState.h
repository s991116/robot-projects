#ifndef MOTORSTATE_H
#define	MOTORSTATE_H

#include "State.h"
#include "Motor.h"
#include "MotorTuningController.h"
#include "DirectionEnum.h"
#include <string>

class MotorState : public State {
public:
    MotorState(Motor* motor, MotorTuningController* motorTuningController);
    State* View();
    virtual ~MotorState();

 private:
    Motor* _Motor;
    MotorTuningController* _MotorTuningController;
    std::string PrintDirection(DirectionEnum dir);
};

#endif	/* MOTORSTATE_H */
