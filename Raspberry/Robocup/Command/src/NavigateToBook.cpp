#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, FollowLineDistance* followLineDistance, MoveDistance* moveDistance, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging) :
NavigateToObject(robotCamera, detectBook1, detectBook2, logging) {

  _RobotCamera = robotCamera;
  _Logging = logging;
  _FollowLineDistance = followLineDistance;
  _MoveDistance = moveDistance;

  _Direction = new Direction(0, 0, 0);

  _NoBookDistance = 250;
  _MoveAfterBook = 20;
  _Book1Finished = false;
  _Book2Finished = false;

  SettingsInt["NOBOOKDISTANCE"]    = &_NoBookDistance;
  SettingsInt["AFTERBOOKDISTANCE"] = &_MoveAfterBook;
  SettingsBool["Book1Finished"]    = &_Object1Finished;
  SettingsBool["Book2Finished"]    = &_Object2Finished;

  _ObjectPosition = new ObjectPosition();
  _DetectBook1 = detectBook1;
  _DetectBook2 = detectBook2;
}

std::string NavigateToBook::Execute(std::vector<int> input) {

  FindObject(CameraMode::FIND_BOOK, _ObjectPosition);
  while(!_ObjectPosition->Detected) {
    this->MoveToNextPosition(_NoBookDistance);
    FindObject(CameraMode::FIND_BOOK, _ObjectPosition);
  }

  _image = _RobotCamera->GetNextFrame(CameraMode::FIND_BOOK_FAST);
  _NavigateBook = CreateBookTemplate(this->_ObjectPosition, _image, 1.0);

  CenterObject(_ObjectPosition->Corner1->GetImageY(), _ObjectPosition->Corner2->GetImageY(), _NavigateBook, CameraMode::FIND_BOOK_FAST);

  MoveToNextPosition(_MoveAfterBook);

  return "";
}

void NavigateToBook::MoveToNextPosition(int distance) {
  if(distance > 0)
  {
    _FollowLineDistance->MoveDistance(distance);
  }
  else
  {
    _Direction->SetDirection(0);
	_Direction->SetRotation(0);
	_Direction->SetSpeed(-6);
    _MoveDistance->Move(_Direction, -distance);
  }
}