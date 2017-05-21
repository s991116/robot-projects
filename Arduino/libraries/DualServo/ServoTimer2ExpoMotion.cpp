#include "ServoTimer2ExpoMotion.h"
#include "Math.h"
#include <Arduino.h>


ServoTimer2ExpoMotion::ServoTimer2ExpoMotion(ServoTimer2* servo, int startPos, int speed) {
    _StartPosition = startPos;
	_EndPosition = startPos;
    _Distance = 0;
    SetSpeed(speed);
    _Position = startPos;
	_Servo = servo;
    _Finished = false;
}

int ServoTimer2ExpoMotion::GetPosition() {
    return _Position;
}

int ServoTimer2ExpoMotion::GetEndPosition() {
    return _EndPosition;
}

void ServoTimer2ExpoMotion::SetSpeed(int speed) {
    _Speed = 10*speed;
    ExpoData::Initialize(_Speed);
}

int ServoTimer2ExpoMotion::GetSpeed() {
    return _Speed / 10;
}

void ServoTimer2ExpoMotion::SetPosition(int pos) {
    _EndPosition = pos;
    _StartPosition = _Position;
    _Distance = _EndPosition - _StartPosition;
    _Finished = false;
	_StartTime = millis();   
   UpdatePosition();
}

void ServoTimer2ExpoMotion::UpdatePosition() {
    if(!_Finished) {
        long dt = _StartTime - millis();    
        float frac = ExpoData::GetData(dt);
        if(frac >0.995) {
            frac = 1.0;
            _Finished = true;        
        }
        _Position = _StartPosition + (_Distance * frac);    
        _Servo->write(_Position);          
    }
}

ServoTimer2ExpoMotion::~ServoTimer2ExpoMotion() {
}