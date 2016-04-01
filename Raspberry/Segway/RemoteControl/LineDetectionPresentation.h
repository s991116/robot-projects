#ifndef LINEDETECTIONPRESENTATION_H
#define	LINEDETECTIONPRESENTATION_H

#include "CameraSensor.h"
#include "Position.h"
#include "ContinuousPresentation.h"

class LineDetectionPresentation : public ContinuousPresentation {
public:
    LineDetectionPresentation(CameraSensor* cameraSensor, Position* position);
    std::string Presentation();
    virtual ~LineDetectionPresentation();
private:
    CameraSensor* _CameraSensor;
    Position* _Position;

};

#endif	/* LINEDETECTIONPRESENTATION_H */

