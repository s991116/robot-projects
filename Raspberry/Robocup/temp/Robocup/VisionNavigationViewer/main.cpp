#include <cstdlib>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CameraDetector.h"
#include "DetectObject.h"
#include "Convert.h"

using namespace std;
using namespace cv;

CameraDetector* cameraDetector;
DetectObject* detectObject;
cv::Mat image;
cv::Mat drawImage;
Position* position;
int PictureNumber = 1;

void UpdateImages() {
  detectObject->GetPosition(image, position);
  
  drawImage = image.clone();
  int circlePointX = (position->PositionX+1.0)/2.0 * image.cols;
  int circlePointY = (position->PositionY+1.0)/2.0 * image.rows;
  circle(drawImage, Point(circlePointX, circlePointY), 10, Scalar(255, 255, 0), 1, 8);
  imshow("Original", drawImage);
  imshow("Thresshold", detectObject->ImgThresholded);
  imshow("OpenClose", detectObject->ImgOpenClose);
}

void switch_callback_HighH( int pos) {
  detectObject->_HighH = pos;
  UpdateImages();
}

void switch_callback_LowH( int pos) {
  detectObject->_LowH = pos;
  UpdateImages();
}

void switch_callback_HighS( int pos) {
  detectObject->_HighS = pos;
  UpdateImages();
}

void switch_callback_LowS( int pos) {
  detectObject->_LowS = pos;
  UpdateImages();
}

void switch_callback_HighV( int pos) {
  detectObject->_HighV = pos;
  UpdateImages();
}

void switch_callback_LowV( int pos) {
  detectObject->_LowV = pos;
  UpdateImages();
}

void switch_callback_Thresshold( int pos) {
  detectObject->_MorphSize = pos;
  UpdateImages();
}

void mouse_callback(int event, int x, int y, int flags, void* userdata) {
  if(event == EVENT_LBUTTONDOWN) {
    image = cameraDetector->GetNextFrameColor();
    UpdateImages();
  }
  
  if(event == EVENT_RBUTTONDOWN) {
    string filename = "DetectObject_";
    string str = Convert::IntToString(PictureNumber);
    PictureNumber++;
    filename += str;
    filename += ".jpg";
    cameraDetector->SavePicture(filename, image);
  }
}

int main(int argc, char** argv) {
  
  cameraDetector = new CameraDetector();
  detectObject = new DetectObject();
  position = new Position();  

  namedWindow("Original");
  namedWindow("Thresshold");
  namedWindow("OpenClose");
    
  cvCreateTrackbar( "HighH", "Thresshold", &detectObject->_HighH, 255, switch_callback_HighH );
  cvCreateTrackbar( "LowH", "Thresshold", &detectObject->_LowH, 255, switch_callback_LowH );
  cvCreateTrackbar( "HighS", "Thresshold", &detectObject->_HighS, 255, switch_callback_HighS );
  cvCreateTrackbar( "LowS", "Thresshold", &detectObject->_LowS, 255, switch_callback_LowS );
  cvCreateTrackbar( "HighV", "Thresshold", &detectObject->_HighV, 255, switch_callback_HighV );
  cvCreateTrackbar( "LowV", "Thresshold", &detectObject->_LowV, 255, switch_callback_LowV );
  cvCreateTrackbar( "MorphSize", "OpenClose", &detectObject->_MorphSize, 10, switch_callback_Thresshold );

  setMouseCallback("Original", mouse_callback, NULL);
  image = cv::imread("Test.jpg", -1);
  UpdateImages();
  waitKey(0);        

  return 0;
}