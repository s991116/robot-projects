#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, ComController* comController, Logging* logging) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _Logging = logging;

  _Direction = new Direction(0, 0, 0);

  _MinDetectPosition = 0.9;
  _NoBookDistance = 400;
  _MoveBookDistanceFactor = 200;
  _MoveBookDistanceOffset = 0.0;
  _MoveBookDistanceMinError = 0.1;
  _MoveAfterBook = 20;
  _Book1Finished = false;
  _Book2Finished = false;

  SettingsFloat["MINPOSITION"]     = &_MinDetectPosition;
  SettingsInt["DISTANCEFACTOR"]    = &_MoveBookDistanceFactor;
  SettingsFloat["DISTANCEOFFSET"]  = &_MoveBookDistanceOffset;
  SettingsFloat["MINERROR"]        = &_MoveBookDistanceMinError;
  SettingsInt["NOBOOKDISTANCE"]    = &_NoBookDistance;
  SettingsInt["AFTERBOOKDISTANCE"] = &_MoveAfterBook;
  SettingsBool["Book1Finished"]    = &_Book1Finished;
  SettingsBool["Book2Finished"]    = &_Book2Finished;

  _DetectBook1 = new ObjectDetect("TemplateBook_1.jpg", &_MinDetectPosition, _Logging);
  _DetectBook2 = new ObjectDetect("TemplateBook_2.jpg", &_MinDetectPosition, _Logging);

  _ObjectPosition = new ObjectPosition();

}

std::string NavigateToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::Blink);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);

  _ObjectPosition = FindBook();

  while(!_ObjectPosition->Detected) {
    this->MoveToNextPosition(_NoBookDistance);
		_ObjectPosition = FindBook();
  }
  
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK_FAST);
  cv::Mat imageRoi = CreateBookTemplate(this->_ObjectPosition, _image);
  _NavigateBook = new ObjectDetect(imageRoi, &_MinDetectPosition, _Logging);
  
  CenterBook(_ObjectPosition->Corner1->GetImageY(), _ObjectPosition->Corner2->GetImageY());

  MoveToNextPosition(_MoveAfterBook);

  return "";
}

cv::Mat NavigateToBook::CreateBookTemplate(ObjectPosition* position, cv::Mat image) {
  
  //Resize
  position->Corner1->SetWidth(image.cols);
  position->Corner1->SetHeight(image.rows);
  position->Corner2->SetWidth(image.cols);
  position->Corner2->SetHeight(image.rows);
  
  cv::Mat imageRoi = image(cv::Rect(
    cv::Point(position->Corner1->GetImageX(), position->Corner1->GetImageY()), 
    cv::Point(position->Corner2->GetImageX(), position->Corner2->GetImageY()))
  );
  cv::imwrite("BookTemplate.jpg", imageRoi );
  
  return imageRoi;
}

ObjectPosition* NavigateToBook::FindBook() {
  _Logging->Log("Searching for book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);

  if(!_Book1Finished)
  {
	_DetectBook1->Detect(_image, _ObjectPosition);
    if(_ObjectPosition->Detected)
    {
	  _Logging->Log("Book-1 found.");
      return _ObjectPosition;
    }
  }

  if(!_Book2Finished)
  {
	_DetectBook1->Detect(_image, _ObjectPosition);
    if(_ObjectPosition->Detected)
    {
      _Logging->Log("Book-2 found.");
    }
    else
    {
      _Logging->Log("No book found.");
    }
  }
  return _ObjectPosition;  
}

void NavigateToBook::CenterBook(int pointX1, int pointX2) {
  _Logging->Log("Centering to book...");

  float error = _ObjectPosition->Center->GetNormalizedX() - _MoveBookDistanceOffset;
  _Logging->Log("Error X:", error);
  while(error > _MoveBookDistanceMinError || error < -_MoveBookDistanceMinError)
  {  
    if(_ObjectPosition->Detected)
    {
      _Logging->Log("Book found.");
      error = _ObjectPosition->Center->GetNormalizedX() - _MoveBookDistanceOffset;
	  int correction = -error *_MoveBookDistanceFactor;
	  
	  _Logging->Log("Move distance: ", correction);
	  this->MoveToNextPosition(correction);	
    }
    else{
      _Logging->Log("Book not found.");
    }
	
	UpdateBookPosition(pointX1, pointX2);
  }
}

void NavigateToBook::UpdateBookPosition(int pointX1, int pointX2) {
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK_FAST);
  cv::Mat imageDetect = _image(cv::Rect(
    cv::Point(0  , pointX1), 
    cv::Point(319, pointX2))
  );
  cv::imwrite("BookSearchTemplate.jpg", imageDetect );  
  _NavigateBook->Detect(imageDetect, _ObjectPosition);
}

void NavigateToBook::MoveToNextPosition(int distance) {
  _Direction->SetDirection(0);
  _Direction->SetRotation(0);
  int speed = 5;
  if(distance > 0) {
    _Direction->SetSpeed(speed);
    this->_ComController->AddDistanceCommand(_Direction, distance);
  }
  else {
    _Direction->SetSpeed(-speed);
    this->_ComController->AddDistanceCommand(_Direction, -distance);
  }
  
  _ComController->StartDistanceCommand();
  int moveDistance = _ComController->DistanceCommandRunning();
  while (moveDistance == 1) {
    usleep(300000);
    moveDistance = _ComController->DistanceCommandRunning();
  }
}