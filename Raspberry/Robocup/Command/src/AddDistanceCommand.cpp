#include "AddDistanceCommand.h"

AddDistanceCommand::AddDistanceCommand(ComController* comController)
{
  this->_ComController = comController;
  _Direction = new Direction(0, 0, 0);
}

std::string AddDistanceCommand::Execute(vector<int> data)
{
  int dir = data[0];
  int speed = data[1];
  int distance = data[2];
  int rotation = data[3];
  _Direction->SetDirection(dir);
  _Direction->SetRotation(rotation);
  _Direction->SetSpeed(speed);
  
  Add(_Direction, distance);
  return "";
}

void AddDistanceCommand::Add(Direction* direction, int distance)
{
    this->_ComController->AddDistanceCommand(direction, distance); 
}