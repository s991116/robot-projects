#include "CameraDetector.h"
#include <iostream>
#include <fstream>


using namespace cv;
using namespace std;

CameraDetector::CameraDetector() {
  _GrayEnabled = false; 
  capture = raspiCamCvCreateCameraCapture(320,240,_GrayEnabled);
}

void CameraDetector::SetGrayMode(bool grayEnabled) {
  if(capture != NULL)
  {
    if(grayEnabled != _GrayEnabled)
    {
      raspiCamCvSetCaptureProperty(capture, 0, grayEnabled);
      _GrayEnabled = grayEnabled;
    }
  }
}

void CameraDetector::IndicateSearchArea(cv::Mat frame, cv::Rect region)
{   
    rectangle(frame, region, cv::Scalar(100,100,80), 2, 8, 0);
}

void CameraDetector::SavePicture(std::string filename, cv::Mat frame) {
    imwrite( filename.c_str(), frame );
}

cv::Mat CameraDetector::GetNextFrame()
{
  SetGrayMode(true);
  this->UpdateFrame();
  return this->imageMat;
}

cv::Mat CameraDetector::GetNextFrameColor()
{
  SetGrayMode(false);
  this->UpdateFrame();
  return this->imageMat;
}

void CameraDetector::UpdateFrame()
{
    this->image = raspiCamCvQueryFrame(this->capture);
    this->imageMat = cv::Mat(this->image);    
}

CameraDetector::~CameraDetector()
{
    raspiCamCvReleaseCapture(&this->capture);        
}