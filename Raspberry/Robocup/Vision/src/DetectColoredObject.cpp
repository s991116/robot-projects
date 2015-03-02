#include <DetectColoredObject.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

DetectColoredObject::DetectColoredObject() {
  _HighH = 5;
  _LowH = 0;

  _HighS = 255;
  _LowS = 92;

  _HighV = 255;
  _LowV = 0;
  
  _MorphSize = 5;
}

void DetectColoredObject::GetPosition(cv::Mat image, Position* position, std::vector< cv::Point2f > scene_corners) {
  Mat imgHSV;

  cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

  inRange(imgHSV, Scalar(_LowH, _LowS, _LowV), Scalar(_HighH, _HighS, _HighV), ImgThresholded); //Threshold the image
  
  //morphological opening (removes small objects from the foreground)
//  erode(ImgThresholded, ImgOpenClose, getStructuringElement(MORPH_ELLIPSE, Size(_MorphSize, _MorphSize)));
//  dilate(ImgOpenClose, ImgOpenClose, getStructuringElement(MORPH_ELLIPSE, Size(_MorphSize, _MorphSize)));

  //morphological closing (removes small holes from the foreground)
//  dilate(ImgOpenClose, ImgOpenClose, getStructuringElement(MORPH_ELLIPSE, Size(_MorphSize, _MorphSize)));
//  erode(ImgOpenClose, ImgOpenClose, getStructuringElement(MORPH_ELLIPSE, Size(_MorphSize, _MorphSize)));
  ImgOpenClose = ImgThresholded;
  
  //Calculate the moments of the thresholded image
  Moments oMoments = moments(ImgOpenClose);

  double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

  //calculate the position of the ball
  int posX = dM10 / dArea;
  int posY = dM01 / dArea;

  int width = image.cols;
  int height = image.rows;
  position->Detected = true;
  
  float normX = (2*posX- width) / (float) width;
  float normY = (2*posY- height) / (float) height;

  position->SetNormalizedPosition(normX, normY, width, height);
}