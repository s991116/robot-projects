#ifndef GYRO_H
#define	GYRO_H

#include "MessageDataProtocol.h"

class Gyro {
public:
    Gyro(MessageDataProtocol* serialProtocol);
    
    short GetAngle();
    
    void SetAnglePid_p(short p);
    void SetAnglePid_i(short i);
    void SetAnglePid_d(short d);
    short GetAnglePid_p();
    short GetAnglePid_i();
    short GetAnglePid_d();
        
    virtual ~Gyro();
private:
    MessageDataProtocol* _SerialProtocol;
};

#endif	/* GYRO_H */