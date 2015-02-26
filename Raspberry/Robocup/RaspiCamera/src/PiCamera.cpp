#include <PiCamera.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

PiCamera::PiCamera() {

  _GrayEnabled = false;
  SetGrayMode(true);
  SetFrameSize(640, 480);
  if (!_Camera.open())
  {
    cerr << "Error opening the camera" << endl;
  }
}

void PiCamera::SetGrayMode(bool grayEnabled) {

  if(grayEnabled != _GrayEnabled)
  {
    _Camera.release();
    _GrayEnabled = grayEnabled;
    if(_GrayEnabled)
    {
      _Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1);
    }
    else
    {
      _Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3);
    }
    _Camera.open();
  }
}

void PiCamera::SetFrameSize(int width, int height) {

  if(width != _Width || height != _Height)
  {
    _Camera.release();
    _Width = width;
    _Height = height;
    _Camera.set( CV_CAP_PROP_FRAME_WIDTH, _Width);
    _Camera.set( CV_CAP_PROP_FRAME_HEIGHT, _Height);
    _Camera.open();
  }
}

cv::Mat PiCamera::GetNextFrame()
{
  _Camera.grab();
  _Camera.retrieve (_ImageMat);
  return _ImageMat;
}

PiCamera::~PiCamera()
{
  _Camera.release();
}
