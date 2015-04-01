#include <CameraNavigation.h>
#include <unistd.h>

CameraNavigation::CameraNavigation(ComController* comController) {
  _ComController = comController;
  _Settings[CameraPosition::FOLLOW_LINE] =           new CameraNavigationSetting(45, 60);
  _Settings[CameraPosition::FIND_BOOK] =             new CameraNavigationSetting(80, 154);
  _Settings[CameraPosition::NAVIGATE_TO_BOOK] =      new CameraNavigationSetting(80, 60 );
  SetPosition(CameraPosition::FOLLOW_LINE);
}

void CameraNavigation::SetPosition(CameraPosition position) {
  if(position != _CurrentPosition)
  {
    SetCameraServoPosition(_Settings[position]->Servo0Position, _Settings[position]->Servo1Position);
    _CurrentPosition = position;
  }
}

void CameraNavigation::SetCameraServoPosition(int servo0Position, int servo1Position) {
   _ComController->SetServoPosition(0, servo0Position);
   _ComController->SetServoPosition(1, servo1Position);
	usleep(700000);
}