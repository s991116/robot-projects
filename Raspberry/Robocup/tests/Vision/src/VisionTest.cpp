#include <DetectSurfObject.h>

#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/nonfree/nonfree.hpp>

using namespace cv;
using namespace std;


bool findObjectSURF( Mat objectMat, Mat sceneMat, int hessianValue );

/** @function main */
int main( int argc, char** argv )
{
 
  Mat img_object = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_scene = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
  DetectObject* detectObject = new DetectSurfObject(img_object, 400);
  Position* pos = new Position(); 

 detectObject->GetPosition(img_scene, pos);
 detectObject->DrawPositionOnImage(img_scene, pos);
  
  std::string filename = "Surf_Output.jpg";
  imwrite(filename.c_str(), img_scene );
  
}