#include "DirectComCommand.h"
#include "Convert.h"

DirectComCommand::DirectComCommand(ComController* comController)
{
    _ComController = comController;
}

std::string DirectComCommand::Execute(vector<int> data)
{    
    int command = data[0];
    int commandData = data[1];

    int response = _ComController->SendCommand(command, commandData);
    
    std::string result =Convert::IntToString(response);
    
    return result;
}
