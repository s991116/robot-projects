#ifndef VISIONTEST_H
#define	VISIONTEST_H

#include <CameraDetector.h>
#include <DetectObject.h>
#include <Position.h>

class VisionTest {
public:
    VisionTest();
    void Execute();    

private:
    
    CameraDetector* _CameraDetector;
    DetectObject* _DetectObject;
    Position* _Position;
};

#endif	/* VISIONTEST_H */