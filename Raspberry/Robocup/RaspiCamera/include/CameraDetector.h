#ifndef CAMERADETECTOR_H
#define	CAMERADETECTOR_H

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <RaspiCamCV.h>
#include <string.h>
#include <ComController.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1};

class CameraDetector {
public:
    CameraDetector(ComController* comController);
	void SetCameraPosition(CameraPosition pos);
    cv::Mat GetNextFrame();
    void IndicateSearchArea(cv::Mat frame, cv::Rect region);
    void SavePicture(std::string filename, cv::Mat frame);
    cv::Mat GetNextFrameColor();
    ~CameraDetector();

private:
    RaspiCamCvCapture* capture;
	ComController* _ComController;
    IplImage* image;
    cv::Mat imageMat;
    void UpdateFrame();
    bool _GrayEnabled;
    void SetGrayMode(bool colorEnabled);
	std::map<CameraPosition, int> Sensor0Position;
	std::map<CameraPosition, int> Sensor1Position;
};

#endif	/* CAMERADETECTOR_H */

