#include "ServoExpoMotion.h"
#include "Math.h"
#include <Arduino.h>

ServoExpoMotion::ServoExpoMotion(Servo* servo, int startPos, int speed) {
    _StartPosition = startPos;
	_EndPosition = startPos;
    _Distance = 0;
	_ExpoData = new ExpoData();
    SetSpeed(speed);
    _Position = startPos;
	_Servo = servo;
    _Finished = false;
}

int ServoExpoMotion::GetPosition() {
    return _Position;
}

int ServoExpoMotion::GetEndPosition() {
    return _EndPosition;
}

void ServoExpoMotion::SetSpeed(int speed) {
    _Speed = 10*speed;
    _ExpoData->Initialize(_Speed);
}

int ServoExpoMotion::GetSpeed() {
    return _Speed / 10;
}

void ServoExpoMotion::SetPosition(int pos) {
    _EndPosition = pos;
    _StartPosition = _Position;
    _Distance = _EndPosition - _StartPosition;
    _Finished = false;
	_StartTime = millis();   
   UpdatePosition();
}

void ServoExpoMotion::UpdatePosition() {
    if(!_Finished) {
        long dt = _StartTime - millis();    
        double frac = _ExpoData->GetData(dt);
        if(frac >0.995) {
            frac = 1.0;
            _Finished = true;        
        }
        _Position = _StartPosition + (_Distance * frac);    
        _Servo->write(_Position);          
    }
}

ServoExpoMotion::~ServoExpoMotion() {
}