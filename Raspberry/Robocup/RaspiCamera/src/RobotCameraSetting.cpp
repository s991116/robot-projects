#include <RobotCameraSetting.h>

RobotCameraSetting::RobotCameraSetting(CameraPosition cameraPos, int frameWidth, int frameHeight, bool grayMode) {
  cameraPosition = cameraPos;
  FrameWidth = frameWidth;
  FrameHeight = frameHeight;
  GrayMode = grayMode;
}