#pragma once

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <string.h>

class PiCamera {
public:
	PiCamera();
	void SetFrameSize(int width, int height);
	void SetGrayMode(bool colorEnabled);
	cv::Mat GetNextFrame();
	~PiCamera();

private:
	raspicam::RaspiCam_Cv _Camera;
	cv::Mat _ImageMat;
	int _Width;
	int _Height;
	bool _GrayEnabled;
};
