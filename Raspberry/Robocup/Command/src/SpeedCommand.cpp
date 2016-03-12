#include "SpeedCommand.h"
#include "Direction.h"

SpeedCommand::SpeedCommand(ComController* comController)
{
    _ComController = comController;
}

std::string SpeedCommand::Execute(vector<int> data)
{
    int dir = data[0];
    int rotation = data[1];
    int speed = data[2];
    Direction* dirSpeed = new Direction(dir, rotation, speed);
    
    _ComController->SetDirection(dirSpeed);
    
    return ""; 
}