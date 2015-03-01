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
  int hesianValue = 400;
  DetectSurfObject* detectObject = new DetectSurfObject(hesianValue);    
  cv::Mat templateImage = cv::imread(templateName, CV_LOAD_IMAGE_GRAYSCALE );
  if(! templateImage.data )                              // Check for invalid input
  {
        std::cerr <<  "Could not open or find the image: '" <<  templateName << "'." << ::endl ;
  }
  detectObject->SetTemplate(templateImage);
  return detectObject;
}

std::string NavigateToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::Blink);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);
  
  _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);

  FindBook();
  
  LogResult();
  
  if(_Book1Found || _Book2Found)
  {
    _ComController->SetLEDMode(LEDColor::Green, LEDMode::On);
  }
  else
  {
    _ComController->SetLEDMode(LEDColor::Green, LEDMode::Off);
  }
  
 return "";
}

void NavigateToBook::FindBook()
{
  _Book1Found = false;
  _Book2Found = false;
  _LoggingSetting->GetLogging()->Log("Searching for book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);  

  _DetectBook1->GetPosition(_image, _Position);
  if(!_Position->Detected)
  {
    _DetectBook2->GetPosition(_image, _Position);
	if(_Position->Detected)
	{
		_Book2Found = true;
	}
  }
  else{
	  _Book1Found = true;
  }
}

void NavigateToBook::LogResult() {
	if(_Book1Found)
	{
		_LoggingSetting->GetLogging()->Log("Book 1 found");
	}
	if(_Book2Found)
	{
		_LoggingSetting->GetLogging()->Log("Book 2 found");
	}
	if(!_Book1Found && !_Book2Found)
	{
		_LoggingSetting->GetLogging()->Log("No book found");
	}		
}