#include "ServoCommand.h"

ServoCommand::ServoCommand(ComController* comController)
{
  this->_ComController = comController;
  for(int i=0; i<this->NrOfServos; i++)
  {
    initialized[i] = false;
  }
}

std::string ServoCommand::Execute(vector<int> data)
{
  int servoNr = data[0];
  int position = data[1];
  if(position != this->position[servoNr])
  {
    this->position[servoNr] = position;
    this->_ComController->SetServoPosition(servoNr, position);
  }
  return "";
}