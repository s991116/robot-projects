#ifndef ROBOTCAMERA_H
#define	ROBOTCAMERA_H

#include <PiCamera.h>
#include <ComController.h>
#include <map>

enum class CameraPosition {FOLLOW_LINE=0, FIND_BOOK=1};

class RobotCamera {
public:
  RobotCamera(PiCamera* piCamera, ComController* comController);
  
  cv::Mat GetNextFrontLineFrame();
  cv::Mat GetNextFrontBallFrame();
  cv::Mat GetNextBookFrame(); 
  
  ~RobotCamera();
  
private:
  PiCamera* _PiCamera;
  ComController* _ComController;
  void SetCameraPosition(CameraPosition pos);
  std::map<CameraPosition, int> _Servo0Position;
  std::map<CameraPosition, int> _Servo1Position;

};

#endif	/* ROBOTCAMERA_H */