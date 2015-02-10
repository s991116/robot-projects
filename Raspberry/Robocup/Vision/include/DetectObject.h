#ifndef DETECTOBJECT_H
#define	DETECTOBJECT_H

#include <Position.h>
#include <CameraDetector.h>

class DetectObject {
public:
    
    virtual void GetPosition(cv::Mat image, Position* position) = 0;
};

#endif	/* DETECTOBJECT_H */