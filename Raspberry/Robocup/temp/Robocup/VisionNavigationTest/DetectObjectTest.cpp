#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "DetectObjectTest.h"
#include "DetectObject.h"
#include "Position.h"

DetectObjectTest::DetectObjectTest() {
  
}

void DetectObjectTest::ImageWithObject() {
  cv::Mat image = cv::imread("ImageWithOjbect.jpg", -1);
  CPPUNIT_ASSERT(image.cols > 0);
  
  DetectObject* detectObject = new DetectObject();
  Position* position = new Position();
  
  detectObject->GetPosition(image, position);
  
  cv::imwrite( "Thresshold.jpg", detectObject->ImgThresholded );
  cv::imwrite( "OpenClose.jpg", detectObject->ImgOpenClose );
  
  
}