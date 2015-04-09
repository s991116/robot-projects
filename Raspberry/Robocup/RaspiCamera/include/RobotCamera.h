#ifndef ROBOTCAMERA_H
#define	ROBOTCAMERA_H

#include <PiCamera.h>
#include <RobotCameraSetting.h>
#include <CameraNavigation.h>

enum class CameraMode {FOLLOW_LINE=0, FIND_BOOK=1, FIND_BALL=2, FIND_BOOK_FAST=3, NAVIGATE_TO_BOOK=4, NAVIGATE_TO_BOOK_FAST=5, FOLLOW_LEFT_TO_LINE=6, FOLLOW_WITH_DOOR_OPEN=7};
enum class ImageMode {FAST_GRAY=0, NORMAL_GRAY=1, FAST_COLOR=2 };

class RobotCamera {
public:
  RobotCamera(PiCamera* piCamera, CameraNavigation* cameraNavigation);
  cv::Mat GetNextFrame(CameraMode cameraMode);
  ~RobotCamera();

private:
  void UpdateCameraPosition(CameraMode cameraMode);
  void SetCameraMode(CameraMode cameraMode);

  PiCamera* _PiCamera;
  CameraNavigation* _CameraNavigation;
  CameraMode _CurrentCameraMode; 

  std::map<CameraMode, RobotCameraSetting*> _CameraMode;
};

#endif	/* ROBOTCAMERA_H */