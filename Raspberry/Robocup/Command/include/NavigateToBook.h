#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToBook : public Command , public Setting {
public:
  NavigateToBook(RobotCamera* robotCamera, ComController* comController);
  std::string Execute(std::vector<int> input);
    
private:
  void SetNavigation(Position* pos);
  DetectSurfObject* CreateDetectObject(std::string templateName);
  RobotCamera* _RobotCamera;
  DetectSurfObject* _DetectBook1;
  DetectSurfObject* _DetectBook2;

  Position* _Position;
  Direction* _Direction;
  ComController* _ComController;    
};

#endif	/* NAVIGATETOBOOK_H */

