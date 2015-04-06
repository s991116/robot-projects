#include <MoveFixedDirCommand.h>
#include <unistd.h>

MoveFixedDirCommand::MoveFixedDirCommand(ComController* comController, Check* check) {
  this->_ComController = comController;
  this->_Check = check;
}

std::string MoveFixedDirCommand::Execute(vector<int> data) {
  int dir = data[0];
  int rotation = data[1];
  int speed = data[2];
  Direction* direction = new Direction(dir, rotation, speed);
  this->_ComController->SetDirection(direction);

  this->_Check->Prepare();

  while (this->_Check->Test()) {
    usleep(50000);
  }

  return "";
}


