#ifndef MOVEDISTANCE_H
#define MOVEDISTANCE_H

#include <AddDistanceCommand.h>
#include <StartDistanceCommand.h>
#include <Direction.h>

class MoveDistance {
  public:
  MoveDistance(AddDistanceCommand* addDistanceCommand, StartDistanceCommand* startDistanceCommand);
  void Move(Direction* direction, int distance);
  
  private:
  AddDistanceCommand* _AddDistanceCommand;
  StartDistanceCommand* _StartDistanceCommand;
};

#endif //MOVEDISTANCE_H