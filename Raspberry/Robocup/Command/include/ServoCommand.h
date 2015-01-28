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
	static const int NrOfServos = 2;
	bool initialized[NrOfServos];
	int position[NrOfServos];
	int maxPosition[NrOfServos];
	int minPosition[NrOfServos];
    ComController* _ComController;
};

#endif	/* SERVOCOMMAND_H */

