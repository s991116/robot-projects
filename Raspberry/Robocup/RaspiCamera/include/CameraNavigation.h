#ifndef CAMERANAVIGATION_H
#define CAMERANAVIGATION_H

#include <ComController.h>
#include <CameraNavigationSetting.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1, NAVIGATE_TO_BOOK=3};

class CameraNavigation {
  public:
  CameraNavigation(ComController* comController);
  void SetPosition(CameraPosition cameraPosition);

  private:
  void SetCameraServoPosition(int servo0, int servo1);
  std::map<CameraPosition, CameraNavigationSetting*> _Settings;

  ComController* _ComController;
  CameraPosition _CurrentPosition;
};

#endif //CAMERANAVIGATION_H

