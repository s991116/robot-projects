#ifndef ADDDISTANCECOMMAND_H
#define	ADDDISTANCECOMMAND_H

#include "Command.h"
#include <ComController.h>
#include <Direction.h>

class AddDistanceCommand : public Command
{
public:
  AddDistanceCommand(ComController* comController);
  std::string Execute(vector<int> data);    
  void Add(Direction* direction, int distance);
  
private:
  ComController* _ComController;
  Direction* _Direction;
};

#endif	/* ADDDISTANCECOMMAND_H */

