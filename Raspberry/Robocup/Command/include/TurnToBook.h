#ifndef TURNTOBOOK_H
#define	TURNTOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <LoggingSetting.h>

class TurnToBook : public Command , public Setting {

public:
  TurnToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting);
  std::string Execute(std::vector<int> input);

private:
  RobotCamera* _RobotCamera;
  ComController* _ComController;
  LoggingSetting* _LoggingSetting;

};

#endif //TURNTOBOOK_H