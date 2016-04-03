#ifndef CAMERASENSOR_H
#define	CAMERASENSOR_H

#include "FaceDetection.h"
#include "PiCamera.h"
#include "Position.h"
#include "Servo.h"
#include "LineDetect.h"

class CameraSensor {
public:
    CameraSensor(PiCamera* piCamera, FaceDetection* faceDetection, LineDetect* lineDetect, Servo* servo);
    void GetFacePosition(Position* position);
    double GetLinePosition();
    void TakePicture(std::string filename);

    virtual ~CameraSensor();
private:
    PiCamera* _PiCamera;
    FaceDetection* _FaceDetection;
    LineDetect* _LineDetect;
    Servo* _Servo;
    float _MoveFactor;
    void MoveToCenter();
    void MoveCamera(Position* position);

};

#endif	/* CAMERASENSOR_H */

