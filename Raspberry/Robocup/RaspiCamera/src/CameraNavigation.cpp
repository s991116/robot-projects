#include <CameraNavigation.h>
#include <unistd.h>

CameraNavigation::CameraNavigation(ComController* comController) {
  _ComController = comController;
  _Settings[CameraPosition::FOLLOW_LINE] =           new CameraNavigationSetting(45, 54);
  _Settings[CameraPosition::FIND_BOOK] =             new CameraNavigationSetting(80, 154);
  _Settings[CameraPosition::NAVIGATE_TO_BOOK] =      new CameraNavigationSetting(80, 54 ); 
  _Settings[CameraPosition::FLOOR_DISTANCE] =        new CameraNavigationSetting(26, 54);
  
  SetCameraServoPosition(CameraPosition::FOLLOW_LINE);
}

void CameraNavigation::SetPosition(CameraPosition position) {
  if(position != _CurrentPosition)
  {
    SetCameraServoPosition(position);
  }
}

void CameraNavigation::SetCameraServoPosition(CameraPosition position) {
  _ComController->SetServoPosition(0, _Settings[position]->Servo0Position);
  _ComController->SetServoPosition(1, _Settings[position]->Servo1Position);
  usleep(600000);
  _CurrentPosition = position;
}