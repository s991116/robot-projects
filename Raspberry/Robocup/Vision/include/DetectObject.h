#ifndef DETECTOBJECT_H
#define	DETECTOBJECT_H

#include <Position.h>
#include <ObjectPosition.h>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class DetectObject {
public:
    virtual void GetPosition(cv::Mat image, ObjectPosition* position) = 0;
	void DrawPositionOnImage(cv::Mat image, ObjectPosition* position);

private:
  cv::Point GetPoint(Position* position);
  
};

#endif	/* DETECTOBJECT_H */