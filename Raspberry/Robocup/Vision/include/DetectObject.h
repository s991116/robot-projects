#ifndef DETECTOBJECT_H
#define	DETECTOBJECT_H

#include <Position.h>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class DetectObject {
public:
    
    virtual void GetPosition(cv::Mat image, Position* position, std::vector< cv::Point2f > scene_corners) = 0;
	
	void DrawPositionOnImage(cv::Mat image, Position* position);
};

#endif	/* DETECTOBJECT_H */