#ifndef MOVEDISTANCE_H
#define MOVEDISTANCE_H

#include <AddDistanceCommand.h>
#include <StartDistanceCommand.h>
#include <Direction.h>
#include <Command.h>

class MoveDistance : public Command {
  public:
  MoveDistance(AddDistanceCommand* addDistanceCommand, StartDistanceCommand* startDistanceCommand);
  std::string Execute(vector<int> data);

  void Move(Direction* direction, int distance);
  
  private:
  AddDistanceCommand* _AddDistanceCommand;
  StartDistanceCommand* _StartDistanceCommand;
  Direction* _Direction;
};

#endif //MOVEDISTANCE_H