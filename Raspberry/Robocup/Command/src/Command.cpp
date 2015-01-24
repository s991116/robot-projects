#include "Command.h"
#include <unistd.h>
#include <cstddef>
#include <iostream>

Command::~Command() {}

DelayCommand::DelayCommand()
{
}

std::string DelayCommand::Execute(vector<int> data)
{
    int delay = data[0];
    usleep(1000 * delay);

    return "";

}

KeyPressCommand::KeyPressCommand()
{    
}

std::string KeyPressCommand::Execute(vector<int> input)
{
    std::cin.get();

    return "";

}