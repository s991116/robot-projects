#include "StartDistanceCommand.h"
#include <unistd.h>

StartDistanceCommand::StartDistanceCommand(ComController* comController) {
  _ComController = comController;
}

std::string StartDistanceCommand::Execute(vector<int> data) {
  StartMoving();
  return "";
}

void StartDistanceCommand::StartMoving()
{
  _ComController->StartDistanceCommand();
  int moveDistance = _ComController->DistanceCommandRunning();
  while (moveDistance == 1) {
    usleep(300000);
    moveDistance = _ComController->DistanceCommandRunning();
  };
}
