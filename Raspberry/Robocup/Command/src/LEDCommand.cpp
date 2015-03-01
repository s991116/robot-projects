#include "LEDCommand.h"

LEDCommand::LEDCommand(ComController* comController)
{
    this->_ComController = comController;
}

std::string LEDCommand::Execute(vector<int> data)
{
    LEDColor LEDNr = static_cast<LEDColor>(data[0]);
    LEDMode mode = static_cast<LEDMode>(data[1]);
	
	this->_ComController->SetLEDMode(LEDNr, mode);

    return "";
}
