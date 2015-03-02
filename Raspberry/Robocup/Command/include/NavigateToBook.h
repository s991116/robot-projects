#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <LoggingSetting.h>

class NavigateToBook : public Command , public Setting {
public:
  NavigateToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting);
  std::string Execute(std::vector<int> input);
    
private:
  void SetNavigation(Position* pos);
  DetectSurfObject* CreateDetectObject(std::string templateName);
  void FindBook();
  void LogResult();
  RobotCamera* _RobotCamera;
  DetectSurfObject* _DetectBook1;
  DetectSurfObject* _DetectBook2;
  bool _Book1Found;
  bool _Book2Found;
  cv::Mat _image;
  std::vector< cv::Point2f > _Scene_corners;
  Position* _Position;
  Direction* _Direction;
  ComController* _ComController;
  LoggingSetting* _LoggingSetting;
};

#endif	/* NAVIGATETOBOOK_H */

