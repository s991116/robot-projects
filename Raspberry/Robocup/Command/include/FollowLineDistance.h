#ifndef FOLLOWLINEDISTANCE_H
#define FOLLOWLINEDISTANCE_H

#include <Command.h>
#include <ComController.h>
#include <FollowLineCommand.h>
#include <DistanceCheck.h>

class FollowLineDistance : public Command {
  public:
  FollowLineDistance(RobotCamera* robotCamera, ComController* comController, FollowLineSetting* followLineSetting, DistanceCheck* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect);
  std::string Execute(vector<int>);
  void MoveDistance(int distance);

  private:
  FollowLineCommand* _FollowLineCommand;
  DistanceCheck* _DistanceCheck;
  ComController* _ComController;
  
};

#endif //FOLLOWLINEDISTANCE_H
