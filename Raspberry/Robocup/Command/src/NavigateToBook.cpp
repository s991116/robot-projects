#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _Position = new Position();
  _Position1_ROI = new Position();
  _Position2_ROI = new Position();
  _Direction = new Direction(0, 0, 0);
  _angleToDistance = 100;
  _DetectBook1 = CreateDetectObject("TemplateBook_1.jpg");
  _DetectBook2 = CreateDetectObject("TemplateBook_2.jpg");
  _LoggingSetting = loggingSetting;
  _Scene_corners = std::vector< cv::Point2f >(4);
}

DetectSurfObject* NavigateToBook::CreateDetectObject(std::string templateName) {
  int hesianValue = 200;
  DetectSurfObject* detectObject = new DetectSurfObject(hesianValue);    
  cv::Mat templateImage = cv::imread(templateName, CV_LOAD_IMAGE_GRAYSCALE );
  if(! templateImage.data )                              // Check for invalid input
  {
        std::cerr <<  "Could not open or find the template image: '" <<  templateName << "'." << ::endl ;
  }
  detectObject->SetTemplate(templateImage);
  return detectObject;
}

std::string NavigateToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::Blink);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);
  _Book1Finished = false;
  _Book2Finished = false;
  int booksTurned = 0;
  for(int bookPlaceNr = 0; bookPlaceNr < 4; bookPlaceNr++)
  {
    if(booksTurned < 2)
    {
      //  this->Turn(90);
      _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);
      BookSearchResult searchResult = FindBook();
      if(searchResult == BookSearchResult::NoBook)
      {
        //this->Turn(-90);
      }
      else{
        cv::Rect ROI = SetSearchArea(_Scene_corners);
		this->_Position1_ROI->SetImagePosition(_Scene_corners[0].x, _Scene_corners[0].y, _image.cols, _image.rows);
		this->_Position2_ROI->SetImagePosition(_Scene_corners[2].x, _Scene_corners[2].y, _image.cols, _image.rows);

        _RobotCamera->GetNextFrame(CameraPosition::NAVIGATE_TO_BOOK);
		
		this->_Position1_ROI->SetWidth(_image.cols);
		this->_Position1_ROI->SetHeight(_image.rows);
		this->_Position2_ROI->SetWidth(_image.cols);
		this->_Position2_ROI->SetHeight(_image.rows);
		
        ShowResult(searchResult);
      }
    }
	//this->MoveToNextPosition(200);
  }
  return "";
}

BookSearchResult NavigateToBook::FindBook() {
  _LoggingSetting->GetLogging()->Log("Searching for book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);  
  
  if(!_Book1Finished)
  {
    _DetectBook1->GetPosition(_image, _Position, &_Scene_corners);
    if(_Position->Detected)
    {
      return BookSearchResult::Book1;
    }
  }

  if(!_Book2Finished)
  {
    _DetectBook2->GetPosition(_image, _Position, &_Scene_corners);
  
    if(_Position->Detected)
    {
      return BookSearchResult::Book2;
    }
  }
  return BookSearchResult::NoBook;
}

void NavigateToBook::Turn(int angle) {
  _Direction->SetDirection(100);
  _Direction->SetRotation(0);
  _Direction->SetSpeed(5);

  int distance = angle * _angleToDistance;

  this->_ComController->AddDistanceCommand(_Direction, distance);
  _ComController->StartDistanceCommand();
  int moveDistance = _ComController->DistanceCommandRunning();
  while (moveDistance == 1) {
    usleep(300000);
    moveDistance = _ComController->DistanceCommandRunning();
  }
}

void NavigateToBook::MoveToNextPosition(int distance) {
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
    _LoggingSetting->GetLogging()->Log("Position1 X:", _Scene_corners[0].x);
    _LoggingSetting->GetLogging()->Log("Position1 Y:", _Scene_corners[0].y);
    _LoggingSetting->GetLogging()->Log("Position2 X:", _Scene_corners[1].x);
    _LoggingSetting->GetLogging()->Log("Position2 Y:", _Scene_corners[1].y);
    _LoggingSetting->GetLogging()->Log("Position3 X:", _Scene_corners[2].x);
    _LoggingSetting->GetLogging()->Log("Position3 Y:", _Scene_corners[2].y);
    _LoggingSetting->GetLogging()->Log("Position4 X:", _Scene_corners[3].x);
    _LoggingSetting->GetLogging()->Log("Position4 Y:", _Scene_corners[3].y);

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

cv::Rect NavigateToBook::SetSearchArea(std::vector< cv::Point2f > corners) {
	cv::Rect result(0,0,0,0);
	return result;
}