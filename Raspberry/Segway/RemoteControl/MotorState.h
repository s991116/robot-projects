#ifndef MOTORSTATE_H
#define	MOTORSTATE_H

#include "State.h"
#include "Motor.h"
#include "DirectionEnum.h"
#include <string>

class MotorState : public State {
public:
    MotorState(Motor* motor);
    State* View();
    virtual ~MotorState();
private:
    Motor* _Motor;
    std::string PrintDirection(DirectionEnum dir);
    std::string ReadString();
    std::string ReadString(std::string text);
    int ReadInteger();
    int ReadInteger(std::string text);
    
};

#endif	/* MOTORSTATE_H */

