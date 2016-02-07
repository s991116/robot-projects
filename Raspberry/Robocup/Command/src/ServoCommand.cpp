#include "ServoCommand.h"

ServoCommand::ServoCommand(ComController* comController)
{
  this->_ComController = comController;
 }

std::string ServoCommand::Execute(vector<int> data)
{
  int servoNr = data[0];
  int position = data[1];
  SetServoPosition(servoNr, position);
  return "";
}

void ServoCommand::SetServoPosition(int servoNr, int position) {
  this->position[servoNr] = position;
  this->_ComController->SetServoPosition(servoNr, position);
}