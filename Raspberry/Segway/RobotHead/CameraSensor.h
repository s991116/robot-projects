#ifndef CAMERASENSOR_H
#define	CAMERASENSOR_H

#include "FaceDetection.h"
#include "PiCamera.h"
#include "Position.h"
#include "Servo.h"

class CameraSensor {
public:
    CameraSensor(PiCamera* piCamera, FaceDetection* faceDetection, Servo* servo);
    bool GetFacePosition(Position* position);
    void TakePicture(std::string filename);

    virtual ~CameraSensor();
private:
    PiCamera* _PiCamera;
    FaceDetection* _FaceDetection;
    Servo* _Servo;
    float _MoveFactor;
    void MoveToCenter();
    void MoveCamera(Position* position);

};

#endif	/* CAMERASENSOR_H */

