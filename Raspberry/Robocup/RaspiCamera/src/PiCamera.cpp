#include <PiCamera.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

PiCamera::PiCamera() {
  _GrayEnabled = false;
  _Width = 320;
  _Height = 240;
  _Capture = raspiCamCvCreateCameraCapture(_Width, _Height, _GrayEnabled);
}

void PiCamera::SetGrayMode(bool grayEnabled) {
  if(_Capture != NULL)
  {
    if(grayEnabled != _GrayEnabled)
    {
	  _GrayEnabled = grayEnabled;
      raspiCamCvSetCaptureProperty(_Capture, 0, _GrayEnabled);
      GetNextFrame();
    }
  }
}

void PiCamera::SetFrameSize(int width, int height) {
  if(width != _Width || height != _Height)
  {
	_Width = width;
	_Height = height;
	raspiCamCvReleaseCapture(&_Capture);
    _Capture = raspiCamCvCreateCameraCapture(_Width, _Height,_GrayEnabled);
	GetNextFrame();
  }
}

cv::Mat PiCamera::GetNextFrame()
{
  UpdateFrame();
  return _ImageMat;
}

void PiCamera::UpdateFrame()
{
    _Image = raspiCamCvQueryFrame(_Capture);
    _ImageMat = cv::Mat(_Image);
}

PiCamera::~PiCamera()
{
    raspiCamCvReleaseCapture(&_Capture);
}