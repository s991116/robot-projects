#ifndef MAINSTATE_H
#define	MAINSTATE_H

#include "State.h"
#include "MotorState.h"

class MainState : public State {
public:
    MainState(State* motorState, State* gyroState, State* servoState);
    virtual ~MainState();

    State* View();
    
private:
    State* Control();
    void Print();
    
    State* _MotorState;
    State* _GyroState;
    State* _ServoState;    
};

#endif	/* MAINSTATE_H */