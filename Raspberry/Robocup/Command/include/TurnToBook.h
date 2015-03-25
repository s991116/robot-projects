#ifndef TURNTOBOOK_H
#define	TURNTOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <Logging.h>
#include <ObjectDetect.h>

class TurnToBook : public Command , public Setting {

public:
  TurnToBook(RobotCamera* robotCamera, ComController* comController, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging);
  std::string Execute(std::vector<int> input);

private:
  RobotCamera* _RobotCamera;
  ComController* _ComController;
  ObjectDetect* _DetectBook1;
  ObjectDetect* _DetectBook2;
  cv::Mat _image;
  Logging* _Logging;
};

#endif //TURNTOBOOK_H