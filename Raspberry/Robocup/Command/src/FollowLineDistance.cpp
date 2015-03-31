#include <FollowLineDistance.h>

FollowLineDistance::FollowLineDistance(RobotCamera* robotCamera, ComController* comController, FollowLineSetting* followLineSetting, DistanceCheck* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect) {
  _DistanceCheck = check;
  _ComController = comController;
  _FollowLineCommand = new FollowLineCommand(robotCamera, comController, followLineSetting, check, bottomLineDetect, topLineDetect);
}

std::string FollowLineDistance::Execute(vector<int> input) {
  int distance = input[0];
  MoveDistance(distance);
  return "";
}

void FollowLineDistance::MoveDistance(int distance) {
  _DistanceCheck->SetDistance(distance);
  _DistanceCheck->Prepare();
  _FollowLineCommand->Execute();
  Direction* dirSpeed = new Direction(0, 0, 0);
  _ComController->SetDirection(dirSpeed);
}