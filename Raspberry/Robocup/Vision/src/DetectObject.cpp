#include <DetectObject.h>

void DetectObject::DrawPositionOnImage(cv::Mat image, Position* position) {
  
  int imagePositionX = position->GetImageX();
  int imagePositionY = position->GetImageY();
    
  cv::Point center = cv::Point(imagePositionX,imagePositionY);
  int radius = 10;
  cv::Scalar color( 255, 0, 0 );
  cv::circle(image, center, radius, color);
}