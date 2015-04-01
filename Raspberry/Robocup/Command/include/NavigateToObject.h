#ifndef NAVIGATETOOBJECT_H
#define NAVIGATETOOBJECT_H

#include <Logging.h>
#include <RobotCamera.h>
#include <ObjectDetect.h>
#include <Setting.h>

#include <opencv/cv.h>

class NavigateToObject : public Setting{

  public:
  NavigateToObject(RobotCamera* robotCamera, ObjectDetect* objectDetect1, ObjectDetect* objectDetect2, Logging* logging);
  void FindObject(CameraMode cameraMode, ObjectPosition* objectPosition);
  void CenterObject(int pointY1, int pointY2, ObjectDetect* objectDetect, CameraMode cameraMode);
  ObjectDetect* CreateBookTemplate(ObjectPosition* position, cv::Mat image, float minDetectPosition);
  bool _Object1Finished;
  bool _Object2Finished;

  private:
  void UpdateObjectPosition(int pointY1, int pointY2, ObjectDetect* objectDetect, CameraMode cameraMode);
  virtual void MoveToNextPosition(int distance) = 0;
  RobotCamera* _RobotCamera;
  Logging* _Logging;
  cv::Mat _image;

  int _MoveDistanceFactor;
  float _MoveDistanceMinError;
  float _MoveDistanceOffset;
  ObjectPosition* _ObjectPosition;
  ObjectDetect* _ObjectDetect1;
  ObjectDetect* _ObjectDetect2;
};

#endif //NAVIGATETOOBJECT_H