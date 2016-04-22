#ifndef DETECTFACE_H
#define	DETECTFACE_H

#include "Position.h"
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>

class DetectFace {
public:
    DetectFace();
    virtual ~DetectFace();
    
    void GetFacePosition(cv::Mat image, Position* position);
       
private:
    cv::CascadeClassifier face_cascade;
};

#endif	/* DETECTFACE_H */

