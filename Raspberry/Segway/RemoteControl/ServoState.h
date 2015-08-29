#ifndef SERVOSTATE_H
#define	SERVOSTATE_H

#include "Servo.h"
#include "State.h"

class ServoState : public State
{
    public:
    ServoState(Servo* servo);
    State* View();
    virtual ~ServoState();
    
    private:
    Servo* _Servo;
};

#endif	/* SERVOSTATE_H */

