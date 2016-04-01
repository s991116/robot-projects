#ifndef CAMERASTATE_H
#define	CAMERASTATE_H

#include "CameraSensor.h"
#include "State.h"
#include "Position.h"
#include "FaceDetectionPresentation.h"
#include "LineDetectionPresentation.h"

class CameraState : public State {
public:
    CameraState(CameraSensor* faceDetection);
    State* View();
    virtual ~CameraState();
    
private:
    CameraSensor* _CameraSensor;
    Position* _Position;
    FaceDetectionPresentation* _FaceDetectionPresentation;
    LineDetectionPresentation* _LineDetectionPresentation;
    int kbhit(void);
};

#endif	/* CAMERASTATE_H */

