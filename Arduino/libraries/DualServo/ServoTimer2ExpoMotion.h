#ifndef SERVOEXPOMOTION_H
#define	SERVOEXPOMOTION_H

#include <ServoTimer2.h>
#include "ExpoData.h"

class ServoTimer2ExpoMotion {
public:
    ServoTimer2ExpoMotion(ServoTimer2* servo, int startPos, int speed);
    int GetPosition();
    int GetEndPosition();
    void SetSpeed(int speed);
    int GetSpeed();
    void SetPosition(int pos);
	void UpdatePosition();
    virtual ~ServoTimer2ExpoMotion();

private:
    void UpdateDistance();
    int _Position, _StartPosition, _EndPosition;
    double _Distance;
    double _Speed;
    unsigned long _StartTime;
    bool _Finished;
	ServoTimer2* _Servo;
};

#endif	/* SERVOPOSITION_H */

