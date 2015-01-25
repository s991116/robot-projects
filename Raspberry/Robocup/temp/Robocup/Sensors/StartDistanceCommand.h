#ifndef STARTDISTANCECOMMAND_H
#define	STARTDISTANCECOMMAND_H
#include <ComController.h>
#include "Command.h"

class StartDistanceCommand : public Command
{
public:
  StartDistanceCommand(ComController* comController);
  std::string Execute(vector<int> data);    
private:
  ComController* _ComController;    
};

#endif	/* STARTDISTANCECOMMAND_H */

