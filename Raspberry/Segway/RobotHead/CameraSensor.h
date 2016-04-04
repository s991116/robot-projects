#ifndef CAMERASENSOR_H
#define	CAMERASENSOR_H

#include "DetectFace.h"
#include "PiCamera.h"
#include "Position.h"
#include "Servo.h"
#include "LineDetect.h"
#include "SensorInfo.h"

class CameraSensor : public SensorInfo {
public:
    CameraSensor(PiCamera* piCamera, DetectFace* detectFace, LineDetect* lineDetect, Servo* servo);
    void GetFacePosition(Position* position);
    LineInfo* GetLine();
    double GetLinePosition();
    void TakePicture(std::string filename);
    std::string GetStatus();

    virtual ~CameraSensor();
private:
    PiCamera* _PiCamera;
    DetectFace* _DetectFace;
    LineDetect* _LineDetect;
    Servo* _Servo;
    float _MoveFactor;
    void MoveToCenter();
    void MoveCamera(Position* position);

};

#endif	/* CAMERASENSOR_H */

