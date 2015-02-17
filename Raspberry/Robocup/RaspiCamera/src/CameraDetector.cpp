#include <CameraDetector.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

CameraDetector::CameraDetector(ComController* comController) {
  _GrayEnabled = false;
  _ComController = comController;
  capture = raspiCamCvCreateCameraCapture(320,240,_GrayEnabled);
  
  Sensor0Position[CameraPosition::FOLLOW_LINE] = 56;
  Sensor1Position[CameraPosition::FOLLOW_LINE] = 108;
  
}

void CameraDetector::SetCameraPosition(CameraPosition pos) {
   _ComController->SetServoPosition(0, Sensor0Position[pos]);
   _ComController->SetServoPosition(1, Sensor1Position[pos]);   
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
