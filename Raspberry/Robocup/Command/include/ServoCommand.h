#ifndef SERVOCOMMAND_H
#define	SERVOCOMMAND_H

#include "Command.h"
#include <ComController.h>

class ServoCommand : public Command
{
public:
  ServoCommand(ComController* comController);
  std::string Execute(vector<int> data);    

private:
  void SetServoPosition(int servoNr, int position);
  static const int NrOfServos = 2;
  int position[NrOfServos];
  ComController* _ComController;
};

#endif	/* SERVOCOMMAND_H */

