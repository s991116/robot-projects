#ifndef GYRO_H
#define	GYRO_H

#include "HardwareController.h"

class Gyro {
public:
    Gyro(HardwareController* hardwareController);
    
    short GetAngle();
    short GetAngleFactor();

    void SetAngleFactor(short factor);
    void SetAngleOffset(short offset);
    short GetAngleOffset();
    short GetAngleAccelration();
    
    void SetAnglePid_p(short p);
    void SetAnglePid_i(short i);
    void SetAnglePid_d(short d);
    short GetAnglePid_p();
    short GetAnglePid_i();
    short GetAnglePid_d();
    
    void SetGyroPidFactor(short factor);
    short GetGyroPidFactor();
    
    short GetPidState();
    void SetPidState(short state);
    
    virtual ~Gyro();
private:
    HardwareController* _HardwareController;
};

#endif	/* GYRO_H */

