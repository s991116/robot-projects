#ifndef NAVIGATE_H
#define	NAVIGATE_H

#include "MessageDataProtocol.h"

class Navigate {
public:
    Navigate(MessageDataProtocol* serialProtocol);
    void ForwardSpeed(short speed);
    void TurnSpeed(short turn);
    short GetForwardSpeed();
    short GetTurnSpeed();
    void EnableSegway();    
    void DisableSegway();
    void SetPID_P(short p);
    void SetPID_I(short i);
    void SetPID_D(short d);
    void SetSpeedCorrLimit(short limit);
    void SetPIDLimit(short limit);
    short GetPID_P();
    short GetPID_I();
    short GetPID_D();
    short GetSpeedCorrLimit();
    short GetPIDLimit();

    virtual ~Navigate();
    
private:
    MessageDataProtocol* _SerialProtocol;
};

#endif	/* NAVIGATE_H */

