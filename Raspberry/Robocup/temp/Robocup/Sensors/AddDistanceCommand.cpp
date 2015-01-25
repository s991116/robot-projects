#include "AddDistanceCommand.h"

AddDistanceCommand::AddDistanceCommand(ComController* comController)
{
    this->_ComController = comController;
}

std::string AddDistanceCommand::Execute(vector<int> data)
{
    int dir = data[0];
    int speed = data[1];
    int distance = data[2];
    int rotation = data[3];
    
    Direction* direction = new Direction(dir, rotation, speed);
    this->_ComController->AddDistanceCommand(direction, distance);

    return "";
}

