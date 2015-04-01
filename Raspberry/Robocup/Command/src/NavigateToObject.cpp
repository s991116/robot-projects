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
  
  cv::Mat imageRoi = image(cv::Rect(
    cv::Point(position->Corner1->GetImageX(), position->Corner1->GetImageY()), 
    cv::Point(position->Corner2->GetImageX(), position->Corner2->GetImageY()))
  );
  cv::imwrite("ObjectTemplate.jpg", imageRoi );
  
  return new ObjectDetect(imageRoi, minDetectPosition, _Logging);
}

void NavigateToObject::CenterObject(int pointY1, int pointY2, ObjectDetect* objectDetect, CameraMode cameraMode) {
  _Logging->Log("Centering to object...");

  UpdateObjectPosition(pointY1, pointY2, objectDetect, cameraMode);
  float error = _ObjectPosition->Center->GetNormalizedX() - _MoveDistanceOffset;
  _Logging->Log("Error X:", error);
  while(error > _MoveDistanceMinError || error < -_MoveDistanceMinError)
  {
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
  objectDetect->Detect(_image, _ObjectPosition, roi);
}