#ifndef CAMERADETECTOR_H
#define	CAMERADETECTOR_H

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <RaspiCamCV.h>
#include <string.h>

class CameraDetector {
public:
    cv::Mat GetNextFrame();
    CameraDetector();
    void IndicateSearchArea(cv::Mat frame, cv::Rect region);
    void SavePicture(std::string filename, cv::Mat frame);
    cv::Mat GetNextFrameColor();
    ~CameraDetector();

private:
    RaspiCamCvCapture* capture;
    IplImage* image;
    cv::Mat imageMat;
    void UpdateFrame();
    bool _GrayEnabled;
    void SetGrayMode(bool colorEnabled);

};

#endif	/* CAMERADETECTOR_H */

