#ifndef CAMERASENSOR_H
#define	CAMERASENSOR_H

#include "PiCamera.h"
#include "Position.h"
#include "Servo.h"
#include "LineDetect.h"
#include <SensorInfo.h>

class CameraSensor : public SensorInfo {
public:
    CameraSensor(PiCamera* piCamera, LineDetect* lineDetect, LineDetect* sensorLineDetect, Servo* servo);
    LineInfo* GetLine();
    LineInfo* GetLine(std::string filename);

    LineInfo* GetSensorLine();
    LineInfo* GetSensorLine(std::string filename);

    double GetLinePosition();
    void UpdateCameraPosition(int horizontal,int vertical);
    void TakePicture(std::string filename);
    std::string GetStatus();
    void UpdateFrameSize(int width, int height);
    LineDetect* _LineDetect;
    LineDetect* _SensorLineDetect;
    virtual ~CameraSensor();
private:
    PiCamera* _PiCamera;
    int _Height;
    int _Width;

    Servo* _Servo;
    float _MoveFactor;
    void MoveToCenter();
    void MoveCamera(Position* position);

};

#endif	/* CAMERASENSOR_H */

