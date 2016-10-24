#ifndef MOTOR_H
#define	MOTOR_H

#include "MessageDataProtocol.h"

class Motor {
public:
    Motor(MessageDataProtocol* serialProtocol);
    void SetLeftP(short p);
    void SetLeftI(short i);
    void SetLeftD(short d);

    short GetLeftP();
    short GetLeftI();
    short GetLeftD();
    
    void SetRightP(short p);
    void SetRightI(short i);
    void SetRightD(short d);

    short GetRightP();
    short GetRightI();
    short GetRightD();

    
    virtual ~Motor();
private:
    MessageDataProtocol* _SerialProtocol;
};

#endif	/* MOTOR_H */

