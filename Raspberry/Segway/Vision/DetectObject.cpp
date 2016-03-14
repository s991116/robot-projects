#include "DetectObject.h"

void DetectObject::DrawPositionOnImage(cv::Mat image, ObjectPosition* position) {
  cv::Scalar color( 255, 0, 0 );

  int radius = 10;
  cv::Point center = GetPoint(position->Center);  
  cv::circle(image, center, radius, color);
 
  cv::Point p1 = GetPoint(position->Corner1);
  cv::Point p2 = GetPoint(position->Corner2);
  
  cv::rectangle(image, p1, p2, color);
}

cv::Point DetectObject::GetPoint(Position* position) {
  int imagePositionX = position->GetImageX();
  int imagePositionY = position->GetImageY();
  cv::Point point = cv::Point(imagePositionX,imagePositionY);
  return point;
}