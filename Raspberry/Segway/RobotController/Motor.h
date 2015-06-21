#ifndef MOTOR_H
#define	MOTOR_H

#include "HardwareController.h"
#include "DirectionEnum.h"

class Motor {
public:
    Motor(HardwareController* hardwareController);
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

    void SetMotorLeftSpeed(short speed);
    void SetMotorRightSpeed(short speed);

    short GetMotorLeftSpeed();
    short GetMotorRightSpeed();
    
    void SetDirection(DirectionEnum direction);
    DirectionEnum GetDirection();
    
    void SetMotorEnabled(bool state);
    
    virtual ~Motor();
private:
    HardwareController* _HardwareController;
    DirectionEnum _Direction;
};

#endif	/* MOTOR_H */

