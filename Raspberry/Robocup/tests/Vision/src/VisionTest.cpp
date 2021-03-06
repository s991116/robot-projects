#include <DetectSurfObject.h>

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
#include <ctime>
#include <EmptyLog.h>

using namespace cv;
using namespace std;


bool findObjectSURF( Mat objectMat, Mat sceneMat, int hessianValue );

/** @function main */
int main( int argc, char** argv )
{
 
  Mat img_object = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_scene = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
  Logging* log = new EmptyLog();
  DetectSurfObject* detectObject = new DetectSurfObject(400, 7, log);
  detectObject->SetTemplate(img_object);
  ObjectPosition* pos = new ObjectPosition(); 
  
  std::clock_t start;
  double duration;
  start = std::clock();
  std::vector< cv::Point2f > _Scene_corners;
  for(int i=0; i<10; ++i)
    detectObject->GetPosition(img_scene, pos);
  
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout<<"Duration time: "<< duration <<'\n';

  detectObject->DrawPositionOnImage(img_scene, pos);
  
  std::string filename = "Surf_Output.jpg";
  imwrite(filename.c_str(), img_scene );
  
}