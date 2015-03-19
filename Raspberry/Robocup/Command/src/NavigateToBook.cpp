#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _LoggingSetting = loggingSetting;

  _Position = new Position();
  _Position1_ROI = new Position();
  _Position2_ROI = new Position();
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
  
  _DetectBook1 = CreateDetectObject("TemplateBook_1.jpg");
  _DetectBook2 = CreateDetectObject("TemplateBook_2.jpg");
  _Scene_corners = std::vector< cv::Point2f >(4);
}

DetectSurfObject* NavigateToBook::CreateDetectObject(std::string templateName) {
  cv::Mat templateImage = cv::imread(templateName, CV_LOAD_IMAGE_GRAYSCALE );
  if(! templateImage.data ) // Check for invalid input
  {
    std::cerr <<  "Could not open or find the template image: '" <<  templateName << "'." << ::endl ;
  }

  return CreateDetectObject(templateImage);
}

DetectSurfObject* NavigateToBook::CreateDetectObject(cv::Mat templateImage) {
  int hesianValue = 100;
  int minGoodMatches = 5;
  DetectSurfObject* detectObject = new DetectSurfObject(hesianValue, minGoodMatches, _LoggingSetting->GetLogging());
  detectObject->SetTemplate(templateImage);
  return detectObject;
}

std::string NavigateToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::Blink);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);

  BookSearchResult searchResult = FindBook();

  while(searchResult == BookSearchResult::NoBook) {
    this->MoveToNextPosition(_NoBookDistance);
    searchResult = FindBook();
  } 

  this->_Position1_ROI->SetImagePosition(_Scene_corners[0].x, _Scene_corners[0].y, _image.cols, _image.rows);
  this->_Position2_ROI->SetImagePosition(_Scene_corners[2].x, _Scene_corners[2].y, _image.cols, _image.rows);
  
  _image = _RobotCamera->GetNextFrame(CameraPosition::NAVIGATE_TO_BOOK);
  
  cv::Mat imageRoi = CreateBookTemplate(this->_Position1_ROI, this->_Position2_ROI, _image);
  _NavigateBook1 = CreateDetectObject(imageRoi);
  
  ShowResult(searchResult);
  CenterBook();

  MoveToNextPosition(_MoveAfterBook);

  return "";
}

cv::Mat NavigateToBook::CreateBookTemplate(Position* position1_ROI, Position* position2_ROI, cv::Mat image) {
  
  position1_ROI->SetWidth(image.cols);
  position1_ROI->SetHeight(image.rows);
  position2_ROI->SetWidth(image.cols);
  position2_ROI->SetHeight(image.rows);
  
  cv::Mat imageRoi = image(cv::Rect(
    cv::Point(position1_ROI->GetImageX(), position1_ROI->GetImageY()), 
    cv::Point(position2_ROI->GetImageX(), position2_ROI->GetImageY()))
  );
  cv::imwrite("BookTemplate.jpg", imageRoi );
  
  return imageRoi;
}

BookSearchResult NavigateToBook::FindBook() {
  _LoggingSetting->GetLogging()->Log("Searching for book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);

  if(!_Book1Finished)
  {
    _DetectBook1->GetPosition(_image, _Position, &_Scene_corners);
    float position = _Position->GetNormalizedX();
	if(_Position->Detected && position >= -_MinDetectPosition && position <= _MinDetectPosition)
    {
      return BookSearchResult::Book1;
    }
  }

  if(!_Book2Finished)
  {
    _DetectBook2->GetPosition(_image, _Position, &_Scene_corners);
    float position = _Position->GetNormalizedX();
    if(_Position->Detected && position >= -_MinDetectPosition && position <= _MinDetectPosition)
    {
      return BookSearchResult::Book2;
    }
  }
  return BookSearchResult::NoBook;
}

void NavigateToBook::CenterBook() {
  _LoggingSetting->GetLogging()->Log("Centering to book...");

  float error = _Position->GetNormalizedX() - _MoveBookDistanceOffset;
  while(error > _MoveBookDistanceMinError || error < -_MoveBookDistanceMinError)
  {  
    if(_Position->Detected)
    {
      _LoggingSetting->GetLogging()->Log("Book found.");
      error = _Position->GetNormalizedX() - _MoveBookDistanceOffset;
	  int correction = -error *_MoveBookDistanceFactor;
	  
	  _LoggingSetting->GetLogging()->Log("Move distance: ", correction);
	  this->MoveToNextPosition(correction);	
    }
    else{
      _LoggingSetting->GetLogging()->Log("Book not found.");
    }
	
	UpdateBookPosition();
  }
}

void NavigateToBook::UpdateBookPosition() {
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);
  cv::Mat imageDetect = _image(cv::Rect(
    cv::Point(0  , _Position1_ROI->GetImageY()), 
    cv::Point(639, _Position2_ROI->GetImageY()))
  );
  cv::imwrite("BookSearchTemplate.jpg", imageDetect );  
  _NavigateBook1->GetPosition(imageDetect, _Position, &_Scene_corners);
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

void NavigateToBook::ShowResult(BookSearchResult result) {
  LogResult(result);
  LEDResult(result);
}

void NavigateToBook::LogResult(BookSearchResult result) {
  if(result == BookSearchResult::Book1)
  {
    _LoggingSetting->GetLogging()->Log("Book 1 found");
  }
  if(result == BookSearchResult::Book2)
  {
    _LoggingSetting->GetLogging()->Log("Book 2 found");
  }
  if(result == BookSearchResult::NoBook)
  {
	_LoggingSetting->GetLogging()->Log("No book found");
  }
  else
  {
    _LoggingSetting->GetLogging()->Log("Position1 X:", _Position1_ROI->GetImageX());
    _LoggingSetting->GetLogging()->Log("Position1 Y:", _Position1_ROI->GetImageY());
    _LoggingSetting->GetLogging()->Log("Position2 X:", _Position2_ROI->GetImageX());
    _LoggingSetting->GetLogging()->Log("Position2 Y:", _Position2_ROI->GetImageY());
	}
}

void NavigateToBook::LEDResult(BookSearchResult result) {
  if(result == BookSearchResult::NoBook)
  {
    _ComController->SetLEDMode(LEDColor::Green, LEDMode::Off);
  }
  else
  {
    _ComController->SetLEDMode(LEDColor::Green, LEDMode::On);
  }
}