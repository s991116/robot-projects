#ifndef IMOTOR_H
#define	IMOTOR_H

class IMotor {
public:
    virtual void SetMotorLeftSpeed(short speed) = 0;
    virtual void SetMotorRightSpeed(short speed) = 0;
};

#endif	/* IMOTOR_H */

