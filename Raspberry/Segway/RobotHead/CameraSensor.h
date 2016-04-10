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
    void UpdateCameraPosition(int horizontal,int vertical);
    void TakePicture(std::string filename);
    std::string GetStatus();
    void UpdateFrameSize(int width, int height);
    LineDetect* _LineDetect;
    virtual ~CameraSensor();
private:
    PiCamera* _PiCamera;
    int _Height;
    int _Width;
    DetectFace* _DetectFace;

    Servo* _Servo;
    float _MoveFactor;
    void MoveToCenter();
    void MoveCamera(Position* position);

};

#endif	/* CAMERASENSOR_H */

