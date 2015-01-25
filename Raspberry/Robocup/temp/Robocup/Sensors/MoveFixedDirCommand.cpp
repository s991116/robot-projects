#include "MoveFixedDirCommand.h"

MoveFixedDirCommand::MoveFixedDirCommand(ComController* comController, Check* check) {
  this->_ComController = comController;
  this->_Check = check;
}

std::string MoveFixedDirCommand::Execute(vector<int> data) {
  int dir = data[0];
  int directionFactor = data[1];
  int speed = data[2];
  Direction* direction = new Direction(dir, directionFactor, speed);
  this->_ComController->SetDirection(direction);

  this->_Check->Prepare();

  while (this->_Check->Test()) {
    usleep(50000);
  }

  return "";
}


