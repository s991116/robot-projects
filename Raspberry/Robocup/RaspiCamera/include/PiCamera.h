#ifndef PICAMERA_H
#define	PICAMERA_H

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <RaspiCamCV.h>
#include <string.h>

class PiCamera {
public:
    PiCamera();
	void SetFrameSize(int width, int height);
    void SetGrayMode(bool colorEnabled);
    cv::Mat GetNextFrame();
    ~PiCamera();

private:
    void UpdateFrame();

    RaspiCamCvCapture* _Capture;
    IplImage* _Image;
    cv::Mat _ImageMat;
	int _Width;
	int _Height;
    bool _GrayEnabled;
};

#endif	/* PICAMERA_H */