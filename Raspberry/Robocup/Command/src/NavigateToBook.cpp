#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, ComController* comController) {
  _RobotCamera = robotCamera;
  _ComController = comController;
  _Position = new Position();
  _Direction = new Direction(0, 0, 0);
  _DetectBook1 = CreateDetectObject("TemplateBook_1.jpg");
  _DetectBook2 = CreateDetectObject("TemplateBook_2.jpg");
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
  _ComController->SetLEDMode(0, LEDMode::Blink);
  _ComController->SetLEDMode(1, LEDMode::Off);
  
  _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);

  cv::Mat image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);  
  _DetectBook1->GetPosition(image, _Position);
  
  if(_Position->Detected)
  {
    _ComController->SetLEDMode(0, LEDMode::On);
  }
  else
  {
    _ComController->SetLEDMode(0, LEDMode::Off);
  }
  
 return "";
}