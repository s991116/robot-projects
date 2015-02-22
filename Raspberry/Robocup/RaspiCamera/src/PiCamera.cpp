#include <PiCamera.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

PiCamera::PiCamera(ComController* comController) {
  _GrayEnabled = false;
  _ComController = comController;
  _width = 320;
  _height = 240;
  capture = raspiCamCvCreateCameraCapture(_width, _height, _GrayEnabled);
  
  _Servo0Position[CameraPosition::FOLLOW_LINE] = 56;
  _Servo1Position[CameraPosition::FOLLOW_LINE] = 108;
  
}

void PiCamera::SetCameraPosition(CameraPosition pos) {
   _ComController->SetServoPosition(0, _Servo0Position[pos]);
   _ComController->SetServoPosition(1, _Servo1Position[pos]);   
}

void PiCamera::SetGrayMode(bool grayEnabled) {
  if(capture != NULL)
  {
    if(grayEnabled != _GrayEnabled)
    {
      raspiCamCvSetCaptureProperty(capture, 0, grayEnabled);
      _GrayEnabled = grayEnabled;
    }
  }
}

void PiCamera::SetFrameSize(int width, int height) {
  if(width != _width || height != _height)
  {
	_width = width;
	_height = height;
	raspiCamCvReleaseCapture(&this->capture);
    capture = raspiCamCvCreateCameraCapture(_width, _height,_GrayEnabled);
  }
}

void PiCamera::IndicateSearchArea(cv::Mat frame, cv::Rect region)
{
    rectangle(frame, region, cv::Scalar(100,100,80), 2, 8, 0);
}

void PiCamera::SavePicture(std::string filename, cv::Mat frame) {
    imwrite( filename.c_str(), frame );
}

cv::Mat PiCamera::GetNextFrame()
{
  SetGrayMode(true);
  this->UpdateFrame();
  return this->imageMat;
}

cv::Mat PiCamera::GetNextFrameColor()
{
  SetGrayMode(false);
  this->UpdateFrame();
  return this->imageMat;
}

void PiCamera::UpdateFrame()
{
    this->image = raspiCamCvQueryFrame(this->capture);
    this->imageMat = cv::Mat(this->image);
}

PiCamera::~PiCamera()
{
    raspiCamCvReleaseCapture(&this->capture);
}
