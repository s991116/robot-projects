#ifndef OBJECTDETECT_H
#define	OBJECTDETECT_H

#include <DetectSurfObject.h>
#include <Logging.h>
#include <Position.h>
#include <ObjectPosition.h>

class ObjectDetect {

public:
  ObjectDetect(std::string templateName, float minDetectPosition, Logging* logging);
  ObjectDetect(cv::Mat templateImage, float minDetectPosition, Logging* logging);  
  bool Detect(cv::Mat image, ObjectPosition* position);
  bool Detect(cv::Mat image, ObjectPosition* position, cv::Rect roi);

private:
  void Setting(float minDetectPosition, Logging* logging);
  bool PositionWithinRange(ObjectPosition* position);

  DetectSurfObject* _DetectObject;
  Logging* _Logging;
  float _MinDetectPosition;
  std::vector< cv::Point2f > _Scene_corners;
  DetectSurfObject* CreateDetectObject(std::string templateName);
  DetectSurfObject* CreateDetectObject(cv::Mat templateImage);  
};

#endif //OBJECTDETECT_H