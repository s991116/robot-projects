#ifndef ADDDISTANCECOMMAND_H
#define	ADDDISTANCECOMMAND_H

#include "Command.h"
#include <ComController.h>

class AddDistanceCommand : public Command
{
public:
    AddDistanceCommand(ComController* comController);
    std::string Execute(vector<int> data);    
private:
    ComController* _ComController;
};

#endif	/* ADDDISTANCECOMMAND_H */

