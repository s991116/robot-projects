#ifndef PICAMERA_H
#define	PICAMERA_H

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <RaspiCamCV.h>
#include <string.h>
#include <ComController.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1};

class PiCamera {
public:
    PiCamera(ComController* comController);
	void SetCameraPosition(CameraPosition pos);
	void SetFrameSize(int width, int height);
    cv::Mat GetNextFrame();
    void IndicateSearchArea(cv::Mat frame, cv::Rect region);
    void SavePicture(std::string filename, cv::Mat frame);
    cv::Mat GetNextFrameColor();
    ~PiCamera();

private:
    RaspiCamCvCapture* capture;
	
	ComController* _ComController;
    IplImage* image;
    cv::Mat imageMat;
	int _width;
	int _height;
    void UpdateFrame();
    bool _GrayEnabled;
    void SetGrayMode(bool colorEnabled);
	std::map<CameraPosition, int> _Servo0Position;
	std::map<CameraPosition, int> _Servo1Position;
};

#endif	/* PICAMERA_H */