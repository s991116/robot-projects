#ifndef TURNTOBOOK_H
#define	TURNTOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <Command.h>
#include <Setting.h>
#include <Logging.h>
#include <ObjectDetect.h>
#include <NavigateToObject.h>
#include <MoveDistance.h>

class TurnToBook : public Command , public NavigateToObject {

public:
  TurnToBook(RobotCamera* robotCamera, MoveDistance* moveDistance, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging);
  std::string Execute(std::vector<int> input);

private:
  void MoveToNextPosition(int distance);

  RobotCamera* _RobotCamera;
  Direction* _Direction;
  ObjectDetect* _DetectBook1;
  ObjectDetect* _DetectBook2;
  MoveDistance* _MoveDistance;
  cv::Mat _image;
  Logging* _Logging;
  ObjectPosition* _ObjectPosition;
  ObjectDetect* _NavigateBook;
};

#endif //TURNTOBOOK_H