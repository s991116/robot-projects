#ifndef RESETMOVECOMMAND_H
#define	RESETMOVECOMMAND_H

#include <ComController.h>
#include "Command.h"

class ResetMoveCommand : public Command {
public:
    ResetMoveCommand(ComController* comController);
    std::string Execute(vector<int> data);
    
private:    
    ComController* _ComController;    
};

#endif	/* RESETMOVECOMMAND_H */

