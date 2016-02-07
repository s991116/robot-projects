#include <MoveDistance.h>

MoveDistance::MoveDistance(AddDistanceCommand* addDistanceCommand, StartDistanceCommand* startDistanceCommand) {
  _AddDistanceCommand = addDistanceCommand;
  _StartDistanceCommand = startDistanceCommand;
  _Direction = new Direction(0,0,0);
}

std::string MoveDistance::Execute(vector<int> data) {
  _Direction->SetDirection(data[0]);
  _Direction->SetRotation(data[1]);
  _Direction->SetSpeed(data[2]);
  int distance = data[3];
  Move(_Direction, distance);
  return "";
}

void MoveDistance::Move(Direction* direction, int distance) {
  _AddDistanceCommand->Add(direction, distance);
  _StartDistanceCommand->StartMoving();
}