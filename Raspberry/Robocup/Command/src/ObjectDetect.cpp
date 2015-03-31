#include <ObjectDetect.h>

ObjectDetect::ObjectDetect(std::string templateName, float minDetectPosition, Logging* logging) {
  Setting(minDetectPosition, logging);
  _DetectObject = CreateDetectObject(templateName);
}

ObjectDetect::ObjectDetect(cv::Mat templateImage, float minDetectPosition, Logging* logging) {
  Setting(minDetectPosition, logging);
  _DetectObject = CreateDetectObject(templateImage);
}

void ObjectDetect::Setting(float minDetectPosition, Logging* logging) {
  _Logging = logging;
  _Scene_corners = std::vector< cv::Point2f >(4);
  _MinDetectPosition = minDetectPosition;
  _Position = new Position();
}

DetectSurfObject* ObjectDetect::CreateDetectObject(std::string templateName) {
  cv::Mat templateImage = cv::imread(templateName, CV_LOAD_IMAGE_GRAYSCALE );
  if(! templateImage.data ) // Check for invalid input
  {
    std::cerr <<  "Could not open or find the template image: '" <<  templateName << "'." << std::endl ;
  }

  return CreateDetectObject(templateImage);
}

DetectSurfObject* ObjectDetect::CreateDetectObject(cv::Mat templateImage) {
  int hesianValue = 100;
  int minGoodMatches = 8;
  DetectSurfObject* detectObject = new DetectSurfObject(hesianValue, minGoodMatches, _Logging);
  detectObject->SetTemplate(templateImage);
  return detectObject;
}

bool ObjectDetect::Detect(cv::Mat image, ObjectPosition* position) {

  _DetectObject->GetPosition(image, position);
  
  float positionX = position->Center->GetNormalizedX();
  if(_Position->Detected && positionX >= -_MinDetectPosition && positionX <= _MinDetectPosition)
  {
    return true;
  }
  return false;
}