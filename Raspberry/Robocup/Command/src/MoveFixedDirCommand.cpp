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

  int test_sleeptime_in_us;
  if(data.size() > 3)
    test_sleeptime_in_us = 1000*data[3];
  else
    test_sleeptime_in_us = 50*1000;
  
  Direction* direction = new Direction(dir, rotation, speed);
  this->_ComController->SetDirection(direction);

  this->_Check->Prepare();

  while (this->_Check->Test()) {
    usleep(test_sleeptime_in_us);
  }

  return "";
}


