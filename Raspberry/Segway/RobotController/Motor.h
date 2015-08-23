#ifndef MOTOR_H
#define	MOTOR_H

#include "IMotor.h"
#include "HardwareController.h"
#include "DirectionEnum.h"

class Motor : public IMotor {
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
    
    short GetMotorLeftDistance();
    short GetMotorRightDistance();

    void SetDirection(DirectionEnum direction);
    DirectionEnum GetDirection();
    
    void SetMotorEnabled(bool state);
    
    short GetMotorSlackCount();
    void  SetMotorSlackCount(short count);

    short GetMotorSlackPWMSpeed();
    void  SetMotorSlackPWMSpeed(short speed);

    short GetMotorSlackMode();
    void  SetMotorSlackMode(short mode);  
   
    void TestMotorSlack(short mode);
    
    virtual ~Motor();
private:
    HardwareController* _HardwareController;
    DirectionEnum _Direction;
};

#endif	/* MOTOR_H */

