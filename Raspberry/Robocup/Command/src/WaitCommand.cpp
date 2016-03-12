#include "WaitCommand.h"
#include <unistd.h>

WaitCommand::WaitCommand(Check* check) {
    _Check = check;
}


std::string WaitCommand::Execute(vector<int> input) {
    _Check->Prepare();
    
    while(_Check->Test())
    {
        usleep(50000);
    }
    
    return "";
}
 


