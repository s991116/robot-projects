#ifndef DETECTCOLOREDOBJECT_H
#define	DETECTCOLOREDOBJECT_H

#include <Position.h>
#include <DetectObject.h>

class DetectColoredObject : public DetectObject {
public:
    DetectColoredObject();
    
    void GetPosition(cv::Mat image, Position* position, std::vector< cv::Point2f > scene_corners);
    cv::Mat ImgThresholded;
    cv::Mat ImgOpenClose;

    int _LowH;
    int _HighH;

    int _LowS; 
    int _HighS;

    int _LowV;
    int _HighV;
    
    int _MorphSize;
    
    private:
};

#endif	/* DETECTCOLOREDOBJECT_H */

