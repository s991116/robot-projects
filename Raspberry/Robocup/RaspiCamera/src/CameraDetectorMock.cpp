#include <CameraDetector.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

CameraDetector::CameraDetector() {
}

void CameraDetector::IndicateSearchArea(cv::Mat frame, cv::Rect region) {
}

void CameraDetector::SavePicture(std::string filename, cv::Mat frame) {
}

cv::Mat CameraDetector::GetNextFrame()
{
  Mat M(2,2, CV_8UC3, Scalar(0,0,255));
  return M;
}

cv::Mat CameraDetector::GetNextFrameColor()
{
  Mat M(2,2, CV_8UC3, Scalar(0,0,255));
  return M;
}

CameraDetector::~CameraDetector()
{
}