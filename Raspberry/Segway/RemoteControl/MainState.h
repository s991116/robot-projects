#ifndef MAINSTATE_H
#define	MAINSTATE_H

#include "State.h"
#include "MotorState.h"

class MainState : public State {
public:
    MainState(State* motorState);
    virtual ~MainState();

    State* View();
    
private:
    State* Control();
    void Print();
    
    State* _MotorState;

};

#endif	/* MAINSTATE_H */