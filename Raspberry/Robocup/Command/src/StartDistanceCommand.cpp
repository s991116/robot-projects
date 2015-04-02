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
  while (_ComController->DistanceCommandRunning() == 1) {
    usleep(300000);
  };
}
