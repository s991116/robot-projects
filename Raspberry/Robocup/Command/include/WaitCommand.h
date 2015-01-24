#ifndef WAITPORTCOMMAND_H
#define	WAITPORTCOMMAND_H
#include "Command.h"
#include "SwitchCheck.h"

class WaitCommand : public Command {
public:
    WaitCommand(Check* check);
    std::string Execute(vector<int> input);
    
private:
    Check* _Check;
};

#endif	/* WAITPORTCOMMAND_H */

