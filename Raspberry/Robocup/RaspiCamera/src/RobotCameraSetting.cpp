#include <RobotCameraSetting.h>

RobotCameraSetting::RobotCameraSetting(int servo0Position, int servo1Position, int frameWidth, int frameHeight, bool grayMode)
{
  Servo0Position = servo0Position;
  Servo1Position = servo1Position;
  FrameWidth = frameWidth;
  FrameHeight = frameHeight;
  GrayMode = grayMode;
}