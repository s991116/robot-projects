#include <NavigateToObject.h>

NavigateToObject::NavigateToObject(RobotCamera* robotCamera, ObjectDetect* objectDetect1, ObjectDetect* objectDetect2, Logging* logging) {
  _RobotCamera = robotCamera;
  _Logging = logging;
  _ObjectDetect1 = objectDetect1;
  _ObjectDetect2 = objectDetect2;
  
  _MoveDistanceFactor = 200;
  _MoveDistanceOffset = 0.0;
  _MoveDistanceMinError = 0.1;

  SettingsInt["DISTANCEFACTOR"]    = &_MoveDistanceFactor;
  SettingsFloat["DISTANCEOFFSET"]  = &_MoveDistanceOffset;
  SettingsFloat["MINERROR"]        = &_MoveDistanceMinError;  
  _ObjectPosition = new ObjectPosition();
  _Object1Finished = false;
  _Object2Finished = false;
}

void NavigateToObject::FindObject(CameraMode cameraMode, ObjectPosition* objectPosition) {
  _Logging->Log("Searching for object...");
  _image = _RobotCamera->GetNextFrame(cameraMode);
  cv::imwrite("SearchForObject.jpg", _image );

  if(!_Object1Finished)
  {
	_ObjectDetect1->Detect(_image, objectPosition);
    if(objectPosition->WithinImage())
    {
	  _Logging->Log("Object-1 found.");
      return;
    }
  }

  if(!_Object2Finished)
  {
	_ObjectDetect2->Detect(_image, objectPosition);
    if(objectPosition->WithinImage())
    {
      _Logging->Log("Object-2 found.");
    }
    else
    {
      _Logging->Log("No object found.");
    }
  }
}

ObjectDetect* NavigateToObject::CreateBookTemplate(ObjectPosition* position, cv::Mat image, float minDetectPosition) {

  //Resize
  position->Corner1->SetWidth(image.cols);
  position->Corner1->SetHeight(image.rows);
  position->Corner2->SetWidth(image.cols);
  position->Corner2->SetHeight(image.rows);
  
  int x1 = position->Corner1->GetLimitedImageX();
  int y1 = position->Corner1->GetLimitedImageY();
  int x2 = position->Corner2->GetLimitedImageX();
  int y2 = position->Corner2->GetLimitedImageY();
  
  _Logging->Log("X1:", x1);
  _Logging->Log("Y1:", y1);
  _Logging->Log("X2:", x2);
  _Logging->Log("Y2:", y2);
  
  cv::Mat imageRoi = image(cv::Rect(
    cv::Point(x1, y1), 
    cv::Point(x2, y2)
  ));
  cv::imwrite("Fast_Object_Template.jpg", imageRoi );
  
  return new ObjectDetect(imageRoi, minDetectPosition, _Logging);
}

void NavigateToObject::CenterObject(int pointY1, int pointY2, ObjectDetect* objectDetect, CameraMode cameraMode) {
  _Logging->Log("Centering to object...");

  UpdateObjectPosition(pointY1, pointY2, objectDetect, cameraMode);
  float error = _ObjectPosition->Center->GetNormalizedX() - _MoveDistanceOffset;

  _Logging->Log("Error: ", error);
  
  _Logging->Log("Min Error: ", _MoveDistanceMinError);
  while(error > _MoveDistanceMinError || error < -_MoveDistanceMinError)
  {
    _Logging->Log("Error X:", error);
    if(_ObjectPosition->Detected)
    {
      _Logging->Log("Object found.");
      error = _ObjectPosition->Center->GetNormalizedX() - _MoveDistanceOffset;
	  int correction = -error *_MoveDistanceFactor;	  
	  _Logging->Log("Move distance: ", correction);
      this->MoveToNextPosition(correction);	
    }
    else{
      _Logging->Log("Object not found.");
    }

	UpdateObjectPosition(pointY1, pointY2, objectDetect, cameraMode);
  }
}

void NavigateToObject::UpdateObjectPosition(int pointY1, int pointY2, ObjectDetect* objectDetect, CameraMode cameraMode) {
  _image = _RobotCamera->GetNextFrame(cameraMode);
  cv::Rect roi = cv::Rect(cv::Point(0  , pointY1), cv::Point(_image.cols, pointY2));
  cv::imwrite("Fast_Search_Image.jpg", _image(roi) );
  objectDetect->Detect(_image, _ObjectPosition, roi);
}