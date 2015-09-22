#ifndef FACEDETECTIONPRESENTATION_H
#define	FACEDETECTIONPRESENTATION_H

#include "CameraSensor.h"
#include "Position.h"
#include "ContinuousPresentation.h"

class FaceDetectionPresentation : public ContinuousPresentation {
public:
    FaceDetectionPresentation(CameraSensor* cameraSensor, Position* position);
    std::string Presentation();
    virtual ~FaceDetectionPresentation();
private:
    CameraSensor* _CameraSensor;
    Position* _Position;

};

#endif	/* FACEDETECTIONPRESENTATION_H */

