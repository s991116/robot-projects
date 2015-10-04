#ifndef FACEDETECTION_H
#define	FACEDETECTION_H

#include "Position.h"
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>

class FaceDetection {
public:
    FaceDetection();
    FaceDetection(const FaceDetection& orig);
    
    bool GetFacePosition(cv::Mat image, Position* position);
    
    virtual ~FaceDetection();
    
private:
    cv::CascadeClassifier face_cascade;
};

#endif	/* FACEDETECTION_H */

