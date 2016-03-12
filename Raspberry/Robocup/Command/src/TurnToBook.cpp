#include <TurnToBook.h>
#include <unistd.h>

TurnToBook::TurnToBook(RobotCamera* robotCamera, MoveDistance* moveDistance, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging) :
NavigateToObject(robotCamera, detectBook1, detectBook2, logging) {

  _RobotCamera = robotCamera;
  _Logging = logging;
  _DetectBook1 = detectBook1;
  _DetectBook2 = detectBook2;
  _MoveDistance = moveDistance;
  _Direction = new Direction(0, 0, 0);
  _TurnSpeed = 2;
  _MinDistance = 10;
  SettingsInt["SPEED"]       = &_TurnSpeed;
  SettingsInt["MINDISTANCE"] = &_MinDistance;

  _ObjectPosition = new ObjectPosition();
}

std::string TurnToBook::Execute(std::vector<int> input) {

  _Logging->Log("Turning towards book...");
  _Direction->SetSpeed(_TurnSpeed);
  FindObject(CameraMode::NAVIGATE_TO_BOOK, _ObjectPosition);
  _image = _RobotCamera->GetNextFrame(CameraMode::NAVIGATE_TO_BOOK_FAST);
  _NavigateBook = CreateBookTemplate(_ObjectPosition, _image, 1.0);
  CenterObject(_ObjectPosition->Corner1->GetImageY(), _ObjectPosition->Corner2->GetImageY(), _NavigateBook, CameraMode::NAVIGATE_TO_BOOK_FAST);
  return "";
}

void TurnToBook::MoveToNextPosition(int distance) {

  distance = -distance;
  if(distance < 0)
  {
	if(distance > -_MinDistance)
		distance = -_MinDistance;
    _Logging->Log("Moving right.");
    _Direction->SetDirection(-100);
    _MoveDistance->Move(_Direction, -distance);
  }
  else
  {
	if(distance < _MinDistance)
		distance = _MinDistance;
	_Logging->Log("Moving left.");
    _Direction->SetDirection(100);
    _MoveDistance->Move(_Direction, distance);
  }
  usleep(1000000);
}
