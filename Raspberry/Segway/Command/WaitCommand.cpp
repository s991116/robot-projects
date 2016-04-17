#include "WaitCommand.h"

WaitCommand::WaitCommand(Check* check) {
    _Check = check;
}

std::string WaitCommand::Execute(vector<int> input) {
    _Check->Prepare();
    
    while(!_Check->Test());
    
    return "Wait command finished.";
}

WaitCommand::~WaitCommand() {
}

