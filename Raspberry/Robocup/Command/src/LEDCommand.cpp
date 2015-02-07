#include "LEDCommand.h"

LEDCommand::LEDCommand(ComController* comController)
{
    this->_ComController = comController;
}

std::string LEDCommand::Execute(vector<int> data)
{
    int LEDNr = data[0];
    int mode = data[1];
    this->_ComController->SetLEDMode(LEDNr, mode);

    return "";
}
