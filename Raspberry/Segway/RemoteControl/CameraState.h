#ifndef CAMERASTATE_H
#define	CAMERASTATE_H

#include "CameraSensor.h"
#include "State.h"
#include "Position.h"
#include "FaceDetectionPresentation.h"

class CameraState : public State {
public:
    CameraState(CameraSensor* faceDetection);
    State* View();
    virtual ~CameraState();
    
private:
    CameraSensor* _CameraSensor;
    Position* _Position;
    FaceDetectionPresentation* _FaceDetectionPresentation;
    int kbhit(void);
    int _PictureCount;
};

#endif	/* CAMERASTATE_H */

