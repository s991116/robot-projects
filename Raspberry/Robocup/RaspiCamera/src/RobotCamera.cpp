#include <RobotCamera.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

RobotCamera::RobotCamera(PiCamera* piCamera, ComController* comController) {
  _PiCamera = piCamera;
  _ComController = comController;  
  _Servo0Position[CameraPosition::FOLLOW_LINE] = 56;
  _Servo1Position[CameraPosition::FOLLOW_LINE] = 108;
  _Servo0Position[CameraPosition::FIND_BOOK] = 56;
  _Servo1Position[CameraPosition::FIND_BOOK] = 108;  
}

cv::Mat RobotCamera::GetNextFrontLineFrame()
{
	SetCameraPosition(CameraPosition::FOLLOW_LINE);
	_PiCamera->SetFrameSize(320,240);
	_PiCamera->SetGrayMode(true);
	return _PiCamera->GetNextFrame();
}

cv::Mat RobotCamera::GetNextBookFrame()
{
	SetCameraPosition(CameraPosition::FIND_BOOK);
	_PiCamera->SetFrameSize(640,480);
	_PiCamera->SetGrayMode(false);
	return _PiCamera->GetNextFrame();
}

cv::Mat RobotCamera::GetNextFrontBallFrame()
{
	SetCameraPosition(CameraPosition::FOLLOW_LINE);
	_PiCamera->SetFrameSize(320,240);
	_PiCamera->SetGrayMode(false);
	return _PiCamera->GetNextFrame();
}

void RobotCamera::SetCameraPosition(CameraPosition pos) {
   _ComController->SetServoPosition(0, _Servo0Position[pos]);
   _ComController->SetServoPosition(1, _Servo1Position[pos]);   
}

RobotCamera::~RobotCamera()
{
  delete _PiCamera;
}