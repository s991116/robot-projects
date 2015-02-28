#include <RobotCamera.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

RobotCamera::RobotCamera(PiCamera* piCamera, ComController* comController) {
  _PiCamera = piCamera;
  _ComController = comController;

  _Settings[CameraPosition::FOLLOW_LINE] = new RobotCameraSetting(56, 108, 320, 240, true);
  _Settings[CameraPosition::FIND_BOOK] = new RobotCameraSetting(101, 108, 640, 480, true);
  _Settings[CameraPosition::FIND_BALL] = new RobotCameraSetting(56, 108, 320, 240, false);  
}

cv::Mat RobotCamera::GetNextFrame(CameraPosition cameraPosition)
{
  SetCameraPosition(_Settings[cameraPosition]->Servo0Position, _Settings[cameraPosition]->Servo1Position);
  _PiCamera->SetFrameSize(_Settings[cameraPosition]->FrameWidth, _Settings[cameraPosition]->FrameHeight);
  _PiCamera->SetGrayMode(_Settings[cameraPosition]->GrayMode);
  return _PiCamera->GetNextFrame();
}

void RobotCamera::SetCameraPosition(int servo0Position, int servo1Position) {
   _ComController->SetServoPosition(0, servo0Position);
   _ComController->SetServoPosition(1, servo1Position);
}

RobotCamera::~RobotCamera()
{
  delete _PiCamera;
}