#ifndef SERVOEXPOMOTION_H
#define	SERVOEXPOMOTION_H

#include <Servo.h>
#include "ExpoData.h"

class ServoExpoMotion {
public:
    ServoExpoMotion(Servo* servo, int startPos, int speed);
    int GetPosition();
    int GetEndPosition();
    void SetSpeed(int speed);
    int GetSpeed();
    void SetPosition(int pos);
	void UpdatePosition();
    virtual ~ServoExpoMotion();

private:
    void UpdateDistance();
    int _Position, _StartPosition, _EndPosition;
    double _Distance;
    double _Speed;
    unsigned long _StartTime;
    bool _Finished;
	Servo* _Servo;
	ExpoData* _ExpoData;
};

#endif	/* SERVOPOSITION_H */

