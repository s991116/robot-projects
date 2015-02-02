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
    int min = data[2];
    int max = data[3];

	if(this->initialized[servoNr])
	{
		if(position != this->position[servoNr])
		{
			this->position[servoNr] = position;
			this->_ComController->SetServoPosition(servoNr, position);
		}
		if(min != this->minPosition[servoNr])
		{
			this->minPosition[servoNr] = min;
			this->_ComController->SetServoMinPosition(servoNr, min);
		}
		if(max != this->maxPosition[servoNr])
		{
			this->maxPosition[servoNr] = max;
			this->_ComController->SetServoMaxPosition(servoNr, max);
		}
	}
	else
	{
		this->position[servoNr] = position;
		this->maxPosition[servoNr] = max;
		this->minPosition[servoNr] = min;
		this->initialized[servoNr] = true;
		this->_ComController->SetServoMaxPosition(servoNr, max);
		this->_ComController->SetServoMinPosition(servoNr, min);
		this->_ComController->SetServoPosition(servoNr, position);
	}

    return "";
}
