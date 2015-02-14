#include <DetectObject.h>

void DetectObject::DrawPositionOnImage(cv::Mat image, Position* position) {
  
  int width = image.cols;
  int height = image.rows;
  
  int imagePositionX = position->GetImagePositionX(width);
  int imagePositionY = position->GetImagePositionY(height);
    
  cv::Point center = cv::Point(imagePositionX,imagePositionY);
  int radius = 10;
  cv::Scalar color( 255, 0, 0 );
  cv::circle(image, center, radius, color);
}