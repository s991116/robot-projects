#include <MoveDistance.h>

MoveDistance::MoveDistance(AddDistanceCommand* addDistanceCommand, StartDistanceCommand* startDistanceCommand) {
  _AddDistanceCommand = addDistanceCommand;
  _StartDistanceCommand = startDistanceCommand;
}

void MoveDistance::Move(Direction* direction, int distance) {
  _AddDistanceCommand->Add(direction, distance);
  _StartDistanceCommand->StartMoving();
}