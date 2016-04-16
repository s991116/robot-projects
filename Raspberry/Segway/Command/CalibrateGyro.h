#ifndef CALIBRATEGYRO_H
#define	CALIBRATEGYRO_H

#include "Command.h"
#include "Setting.h"
#include "Navigate.h"
#include "Gyro.h"

class CalibrateGyro : public Command , public Setting{
public:
    CalibrateGyro(Navigate* navigate, Gyro* gyro);
    std::string Execute(vector<int> input);
    virtual ~CalibrateGyro();
private:
    Navigate* _Navigate;
    Gyro* _Gyro;
    
    int PID_P;
    int PID_I;
    int PID_D;
};

#endif	/* CALIBRATEGYRO_H */

