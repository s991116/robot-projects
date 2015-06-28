#ifndef GYROSTATE_H
#define	GYROSTATE_H

#include "State.h"
#include "Gyro.h"

class GyroState : public State {
public:
    GyroState(Gyro* gyro);
    State* View();
    virtual ~GyroState();
private:
    Gyro* _Gyro;
};

#endif	/* GYROSTATE_H */

