#ifndef ROBOTCAMERASETTING_H
#define	ROBOTCAMERASETTING_H

#include <CameraNavigation.h>

class RobotCameraSetting {
public:
  RobotCameraSetting(CameraPosition cameraPos, int frameWidth, int frameHeight, bool grayMode);

  CameraPosition cameraPosition;
  int FrameWidth;
  int FrameHeight;
  bool GrayMode;
};

#endif	/* ROBOTCAMERASETTING_H */