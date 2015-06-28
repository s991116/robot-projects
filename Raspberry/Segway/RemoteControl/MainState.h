#ifndef MAINSTATE_H
#define	MAINSTATE_H

#include "State.h"
#include "MotorState.h"

class MainState : public State {
public:
    MainState(State* motorState, State* gyroState);
    virtual ~MainState();

    State* View();
    
private:
    State* Control();
    void Print();
    
    State* _MotorState;
    State* _GyroState;
};

#endif	/* MAINSTATE_H */