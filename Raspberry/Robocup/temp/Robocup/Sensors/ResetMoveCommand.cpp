#include "ResetMoveCommand.h"

ResetMoveCommand::ResetMoveCommand(ComController* comController)
{
    this->_ComController = comController;
}

std::string ResetMoveCommand::Execute(vector<int> data)
{
    this->_ComController->ResetMoveCommand();
    
    return ""; 
}


