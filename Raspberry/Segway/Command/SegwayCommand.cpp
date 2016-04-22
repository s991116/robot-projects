#include "SegwayCommand.h"

SegwayCommand::SegwayCommand(Navigate* navigate) {
    _Navigate = navigate;
}

std::string SegwayCommand::Execute(vector<int> input) {
    if(input.size() == 0 || input[0] == 1)
    {
      _Navigate->ForwardSpeed(0);
      _Navigate->TurnSpeed(0);
      _Navigate->EnableSegway();
      
      
      
      return "Segway enabled";    
    }
    else
    {
      _Navigate->DisableSegway();
      return "Segway disabled";            
    }
}

SegwayCommand::~SegwayCommand() {
}

