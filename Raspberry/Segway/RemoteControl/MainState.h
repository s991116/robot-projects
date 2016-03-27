#ifndef MAINSTATE_H
#define	MAINSTATE_H

#include "State.h"
#include "MotorState.h"

class MainState : public State {
public:
    MainState(State* motorState, State* gyroState, State* servoState, State* CameraState, State* comState);
    virtual ~MainState();

    State* View();
    
private:
    State* Control();
    void Print();
    
    State* _MotorState;
    State* _GyroState;
    State* _ServoState;    
    State* _CameraState;
    State* _ComState;
};

#endif	/* MAINSTATE_H */