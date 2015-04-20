#ifndef CAMERANAVIGATION_H
#define CAMERANAVIGATION_H

#include <ComController.h>
#include <CameraNavigationSetting.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1, NAVIGATE_TO_BOOK=2, FLOOR_DISTANCE=3, FOLLOW_LEFT_TO_LINE=4, FOLLOW_WITH_DOOR_OPEN = 5, FOLLOW_LINE_FAST = 6};

class CameraNavigation {
  public:
  CameraNavigation(ComController* comController);
  void SetPosition(CameraPosition cameraPosition);

  private:
  void SetCameraServoPosition(CameraPosition cameraPosition);
  std::map<CameraPosition, CameraNavigationSetting*> _Settings;

  ComController* _ComController;
  CameraPosition _CurrentPosition;
};

#endif //CAMERANAVIGATION_H

