#include <RobotCamera.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace cv;
using namespace std;

RobotCamera::RobotCamera(PiCamera* piCamera, ComController* comController) {
  _PiCamera = piCamera;
  _ComController = comController;

  _Settings[CameraPosition::FOLLOW_LINE] = new RobotCameraSetting(45, 60, 320, 240, true);
  _Settings[CameraPosition::FIND_BOOK] = new RobotCameraSetting(80, 154, 640, 480, true);
  _Settings[CameraPosition::FIND_BALL] = new RobotCameraSetting(45, 60, 320, 240, false);
  _Settings[CameraPosition::FIND_BOOK_FAST] = new RobotCameraSetting(80, 154, 320, 240, true);
  _Settings[CameraPosition::NAVIGATE_TO_BOOK] = new RobotCameraSetting(80, 60, 640, 480, true);
  
  UpdateCameraPosition(CameraPosition::FOLLOW_LINE);
}

cv::Mat RobotCamera::GetNextFrame(CameraPosition cameraPosition)
{
  if(cameraPosition != _CurrentCameraPosition)
  {
    UpdateCameraPosition(cameraPosition);
    usleep(300000);
    image = _PiCamera->GetNextFrame();
    usleep(400000);
    image = _PiCamera->GetNextFrame();
    return image;
  }
  return _PiCamera->GetNextFrame();
}

void RobotCamera::UpdateCameraPosition(CameraPosition cameraPosition)
{
  SetCameraServoPosition(_Settings[cameraPosition]->Servo0Position, _Settings[cameraPosition]->Servo1Position);
  _PiCamera->SetFrameSize(_Settings[cameraPosition]->FrameWidth, _Settings[cameraPosition]->FrameHeight);
  _PiCamera->SetGrayMode(_Settings[cameraPosition]->GrayMode);
  _CurrentCameraPosition = cameraPosition;
}

void RobotCamera::SetCameraServoPosition(int servo0Position, int servo1Position) {
   _ComController->SetServoPosition(0, servo0Position);
   _ComController->SetServoPosition(1, servo1Position);
}

RobotCamera::~RobotCamera()
{
  delete _PiCamera;
}