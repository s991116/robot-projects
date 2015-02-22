#include <NavigateToBook.h>

NavigateToBook::NavigateToBook(RobotCamera* robotCamera, DetectSurfObject* detectObject, ComController* comController) {
  _RobotCamera = robotCamera;
  _DetectObject = detectObject;
  _ComController = comController;
  _Position = new Position();
  _Direction = new Direction(0, 0, 0);  
}

std::string NavigateToBook::Execute(std::vector<int> input) {

  cv::Mat object = cv::imread("template.jpg", CV_LOAD_IMAGE_GRAYSCALE );
  _DetectObject->SetTemplate(object);

  cv::Mat image = _RobotCamera->GetNextFrame(CameraPosition::FIND_BOOK);  
  _DetectObject->GetPosition(image, _Position);
    
  SetNavigation(_Position);
  _ComController->StartDistanceCommand();
  while(_ComController->DistanceCommandRunning())
  {
  }		
	
 return "";
}

void NavigateToBook::SetNavigation(Position* pos) {
  
  _Direction->SetRotation(0);
  _Direction->SetSpeed(8);
  if (pos->PositionX > 0) //Turn 90 degree clockwise/right
  {
	 _Direction->SetDirection(100);
    _ComController->AddDistanceCommand(_Direction, 500);  
  }
  else //Turn 90 degree anti-clockwise/left
  {
	 _Direction->SetDirection(-100);
    _ComController->AddDistanceCommand(_Direction, 500);  
  }
  
  //Move straight
  _Direction->SetDirection(0);
  _ComController->AddDistanceCommand(_Direction, 500);

  if (pos->PositionX > 0) //Turn 90 degree anti-clockwise/left
  {
	 _Direction->SetDirection(-100);
    _ComController->AddDistanceCommand(_Direction, 500);  
  }
  else //Turn 90 degree clockwise/right
  {
	 _Direction->SetDirection(100);
    _ComController->AddDistanceCommand(_Direction, 500);  
  }
}