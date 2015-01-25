#ifndef DETECTOBJECT_H
#define	DETECTOBJECT_H

#include "CameraDetector.h"
#include "Position.h"


class DetectObject {
public:
    DetectObject();
    
    void GetPosition(cv::Mat image, Position* position);
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

#endif	/* DETECTOBJECT_H */

