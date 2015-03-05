#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _Position = new Position();
  _Direction = new Direction(0, 0, 0);
  _DetectBook1 = CreateDetectObject("TemplateBook_1.jpg");
  _DetectBook2 = CreateDetectObject("TemplateBook_2.jpg");
  _LoggingSetting = loggingSetting;
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
  
  _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);

  BookSearchResult searchResult = FindBook();
  
  ShowResult(searchResult);  
 return "";
}

BookSearchResult NavigateToBook::FindBook()
{
  _LoggingSetting->GetLogging()->Log("Searching for book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);  
  
  _DetectBook1->GetPosition(_image, _Position, _Scene_corners);
  if(_Position->Detected)
  {
    return BookSearchResult::Book1;
  }
  
  _DetectBook2->GetPosition(_image, _Position, _Scene_corners);
  if(_Position->Detected)
  {
    return BookSearchResult::Book2;
  }
  return BookSearchResult::NoBook;
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
    _LoggingSetting->GetLogging()->Log("Position X:", _Position->GetNormalizedX());
    _LoggingSetting->GetLogging()->Log("Position Y:", _Position->GetNormalizedY());
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