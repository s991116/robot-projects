#ifndef ROBOTCAMERA_H
#define	ROBOTCAMERA_H

#include <PiCamera.h>
#include <RobotCameraSetting.h>
#include <ComController.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1, FIND_BALL=2,  NAVIGATE_TO_BOOK=3};

class RobotCamera {
public:
  RobotCamera(PiCamera* piCamera, ComController* comController);
  
  cv::Mat GetNextFrame(CameraPosition cameraPosition);
  
  ~RobotCamera();
  
private:
  PiCamera* _PiCamera;
  ComController* _ComController;
  CameraPosition _CurrentCameraPosition;
  void SetCameraPosition(int servo0, int servo1);
  std::map<CameraPosition, RobotCameraSetting*> _Settings;
  cv::Mat image;
};

#endif	/* ROBOTCAMERA_H */