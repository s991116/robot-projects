#ifndef GYRO_H
#define	GYRO_H

#include "HardwareController.h"

class Gyro {
public:
    Gyro(HardwareController* hardwareController);
    
    short GetAngel();
    short GetAngelFactor();

    void SetAngelFactor(short factor);
    short GetAngelAccelration();
    
    void SetAngelPid_p(short p);
    void SetAngelPid_i(short i);
    void SetAngelPid_d(short d);
    short GetAngelPid_p();
    short GetAngelPid_i();
    short GetAngelPid_d();
    
    void SetGyroPidFactor(short factor);
    short GetGyroPidFactor();
    
    short GetPidState();
    void SetPidState(short state);
    
    virtual ~Gyro();
private:
    HardwareController* _HardwareController;
};

#endif	/* GYRO_H */

