#ifndef GYRO_H
#define	GYRO_H

#include "SerialProtocol.h"

class Gyro {
public:
    Gyro(SerialCommandProtocol* serialProtocol);
    
    short GetAngle();
    
    void SetAnglePid_p(short p);
    void SetAnglePid_i(short i);
    void SetAnglePid_d(short d);
    short GetAnglePid_p();
    short GetAnglePid_i();
    short GetAnglePid_d();
        
    virtual ~Gyro();
private:
    SerialCommandProtocol* _SerialProtocol;
};

#endif	/* GYRO_H */