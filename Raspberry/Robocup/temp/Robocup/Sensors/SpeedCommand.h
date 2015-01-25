#ifndef SPEEDCOMMAND_H
#define	SPEEDCOMMAND_H

#include <ComController.h>
#include "Command.h"

class SpeedCommand : public Command {
public:
    SpeedCommand(ComController* comController);
    std::string Execute(vector<int> data);
    
private:
    ComController* _ComController;
};

#endif	/* SPEEDCOMMAND_H */

