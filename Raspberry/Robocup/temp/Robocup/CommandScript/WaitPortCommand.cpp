#include "WaitCommand.h"


WaitCommand::WaitCommand(SwitchCheck* check) {
    _SwitchCheck = check;
}


vector<int> WaitCommand::Execute(vector<int> input) {
    _SwitchCheck->_CurrentCheck->Prepare();
    
    while(_SwitchCheck->_CurrentCheck->Test())
    {
        usleep(50000);
    }
    
    vector<int> result;
    return result;
}
 

