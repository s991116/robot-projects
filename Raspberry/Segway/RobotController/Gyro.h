#ifndef GYRO_H
#define	GYRO_H

#include "HardwareController.h"

class Gyro {
public:
    Gyro(HardwareController* hardwareController);
    
    short GetAngle();
    void SetAngleFactor(short factor);
    short GetAngleFactor();
    short GetAngleAccelration();
    
    virtual ~Gyro();
private:
    HardwareController* _HardwareController;
};

#endif	/* GYRO_H */

