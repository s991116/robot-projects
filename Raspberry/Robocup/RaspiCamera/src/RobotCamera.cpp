#include <RobotCamera.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace cv;
using namespace std;

RobotCamera::RobotCamera(PiCamera* piCamera, CameraNavigation* cameraNavigation) {
  _PiCamera = piCamera;
  _CameraNavigation = cameraNavigation;
  _CurrentCameraMode = CameraMode::FOLLOW_LINE;

  _CameraMode[CameraMode::FOLLOW_LINE]           = new RobotCameraSetting(CameraPosition::FOLLOW_LINE,      320, 240, true);
  _CameraMode[CameraMode::FIND_BOOK]             = new RobotCameraSetting(CameraPosition::FIND_BOOK,        640, 480, true);
  _CameraMode[CameraMode::FIND_BALL]             = new RobotCameraSetting(CameraPosition::FOLLOW_LINE,      320, 240, false);
  _CameraMode[CameraMode::FIND_BOOK_FAST]        = new RobotCameraSetting(CameraPosition::FIND_BOOK,        320, 240, true);
  _CameraMode[CameraMode::NAVIGATE_TO_BOOK]      = new RobotCameraSetting(CameraPosition::NAVIGATE_TO_BOOK, 640, 480, true);
  _CameraMode[CameraMode::NAVIGATE_TO_BOOK_FAST] = new RobotCameraSetting(CameraPosition::NAVIGATE_TO_BOOK, 320, 240, true);
	
  UpdateCameraPosition(CameraMode::FOLLOW_LINE);
  SetCameraMode(CameraMode::FOLLOW_LINE);
}

cv::Mat RobotCamera::GetNextFrame(CameraMode cameraMode)
{
  UpdateCameraPosition(cameraMode);
  return _PiCamera->GetNextFrame();
}

void RobotCamera::UpdateCameraPosition(CameraMode cameraMode)
{
   _CameraNavigation->SetPosition(_CameraMode[cameraMode]->cameraPosition);
  if(cameraMode != _CurrentCameraMode)
  {
    SetCameraMode(cameraMode);
  }
}

void RobotCamera::SetCameraMode(CameraMode cameraMode)
{
  RobotCameraSetting* cameraSetting = _CameraMode[cameraMode];
  _PiCamera->SetFrameSize(cameraSetting->FrameWidth, cameraSetting->FrameHeight);
  _PiCamera->SetGrayMode(cameraSetting->GrayMode);
  _PiCamera->GetNextFrame();
  usleep(300000);
  _PiCamera->GetNextFrame();
  _CurrentCameraMode = cameraMode;
}

RobotCamera::~RobotCamera()
{
  delete _PiCamera;
}