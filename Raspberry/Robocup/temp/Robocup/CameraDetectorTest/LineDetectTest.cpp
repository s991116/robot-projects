#include "LineDetectTest.h"
#include "LineInfo.h"
#include "LineDetect.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "EmptyLog.h"

LineDetectTest::LineDetectTest() {
  _Logging = new EmptyLog();
}

cv::Mat LineDetectTest::CreateEmptyImage(uchar backgroundValue) {
  int imageWidth = 200;
  int imageHeight = 100;

  cv::Mat EmptyImage(imageHeight, imageWidth, CV_8U, cv::Scalar::all(backgroundValue));
  return EmptyImage;
}

void LineDetectTest::AddHorizontalLine(cv::Mat image, int lineStart, int lineEnd, uchar color) {
  cv::Size size = image.size();

  for (int x = 0; x < size.height; x++)
    for (int y = lineStart; y < lineEnd; y++) {
      image.at<uchar>(x, y) = color;
    }
}

void LineDetectTest::AddVerticalLine(cv::Mat image, int lineStart, int lineEnd, uchar color) {
  cv::Size size = image.size();

  for (int y = 0; y < size.width; y++)
    for (int x = lineStart; x < lineEnd; x++) {
      image.at<uchar>(x, y) = color;
    }
}

cv::Rect LineDetectTest::CreateVerticalLineSearchArea(int imageWidth, int sensorLow, int sensorHigh) {
  cv::Rect roi(0, sensorLow, imageWidth, sensorHigh - sensorLow);
  return roi;
}

cv::Rect LineDetectTest::CreateHorizontalLineSearchArea(int imageHeight, int sensorLow, int sensorHigh) {
  cv::Rect roi(sensorLow, 0, sensorHigh - sensorLow, imageHeight);
  return roi;
}

void LineDetectTest::NoLineInImageLineNotFound() {

  cv::Mat NoLineImage = CreateEmptyImage(LineDetectTest::BlackColor);
  cv::Size size = NoLineImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;

  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::LEFT, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(NoLineImage);

  CPPUNIT_ASSERT_EQUAL(false, lineInfo->LineDetected());
}

void LineDetectTest::LineInImageCenterLineFound() {

  int lineStart = 90;
  int lineEnd = 110;

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, lineStart, lineEnd, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT_EQUAL(100, lineInfo->GetPosition());
}

void LineDetectTest::LineInImageLineFound() {

  int lineStart = 90;
  int lineEnd = 110;

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, lineStart, lineEnd, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::LEFT, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);
  LineInImage.release();

  CPPUNIT_ASSERT_EQUAL(true, lineInfo->LineDetected());
}

void LineDetectTest::FindLeftLinePosition() {

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, 20, 40, LineDetectTest::WhitekColor);
  AddHorizontalLine(LineInImage, 120, 140, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;

  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::LEFT, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT(20 >= lineInfo->GetPosition());
}

void LineDetectTest::FindRightLinePosition() {

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, 20, 40, LineDetectTest::WhitekColor);
  AddHorizontalLine(LineInImage, 120, 140, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::RIGHT, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT(140 <= lineInfo->GetPosition());
}

void LineDetectTest::FindPositionForInverseColorLine() {
  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::WhitekColor);
  AddHorizontalLine(LineInImage, 20, 40, LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, 120, 140, LineDetectTest::BlackColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::RIGHT, LineDetectSetting::VERTICAL, true);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);
  CPPUNIT_ASSERT(140 <= lineInfo->GetPosition() && 160 >= lineInfo->GetPosition());
}

void LineDetectTest::FindLineWhenLineAtImageBorderRight() {

  int lineStart = 180;
  int lineEnd = 200;

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, lineStart, lineEnd, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT(lineInfo->GetPosition() > 180);
  CPPUNIT_ASSERT(lineInfo->LineDetected());
}

void LineDetectTest::FindLineWhenLineAtImageBorderLeft() {

  int lineStart = 0;
  int lineEnd = 20;

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddHorizontalLine(LineInImage, lineStart, lineEnd, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateVerticalLineSearchArea(size.width, 50, 70);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT(lineInfo->GetPosition() < 20);
  CPPUNIT_ASSERT(lineInfo->LineDetected());
}

void LineDetectTest::NoHorizontalLineInImageLineNotFound() {

  cv::Mat NoLineImage = CreateEmptyImage(LineDetectTest::BlackColor);
  cv::Size size = NoLineImage.size();
  cv::Rect roi = CreateHorizontalLineSearchArea(size.height, 50, 60);

  int filterHalf = 3;
  int filterThresshold = 5;

  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::LEFT, LineDetectSetting::HORIZONTAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  lineDetectSetting->SetPosition(LineDetectSetting::LEFT);
  LineInfo* lineInfo = lineDetect->DetectLine(NoLineImage);
  CPPUNIT_ASSERT_EQUAL(false, lineInfo->LineDetected());

  lineDetectSetting->SetPosition(LineDetectSetting::RIGHT);
  lineInfo = lineDetect->DetectLine(NoLineImage);
  CPPUNIT_ASSERT_EQUAL(false, lineInfo->LineDetected());

  lineDetectSetting->SetPosition(LineDetectSetting::CENTER);
  lineInfo = lineDetect->DetectLine(NoLineImage);
  CPPUNIT_ASSERT_EQUAL(false, lineInfo->LineDetected());

}

void LineDetectTest::HorizontalLineInImageCenterLineFound() {

  int lineStart = 50;
  int lineEnd = 60;

  cv::Mat LineInImage = CreateEmptyImage(LineDetectTest::BlackColor);
  AddVerticalLine(LineInImage, lineStart, lineEnd, LineDetectTest::WhitekColor);

  cv::Size size = LineInImage.size();
  cv::Rect roi = CreateHorizontalLineSearchArea(size.height, 50, 60);

  int filterHalf = 3;
  int filterThresshold = 5;
  LineDetectSetting* lineDetectSetting = new LineDetectSetting(roi, filterHalf, filterThresshold, LineDetectSetting::CENTER, LineDetectSetting::HORIZONTAL, false);
  LineDetect* lineDetect = new LineDetect(lineDetectSetting, _Logging);

  lineDetectSetting->SetPosition(LineDetectSetting::CENTER);
  LineInfo* lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT_EQUAL(true, lineInfo->LineDetected());
  CPPUNIT_ASSERT_EQUAL(55, lineInfo->GetPosition());

  lineDetectSetting->SetPosition(LineDetectSetting::LEFT);
  lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT_EQUAL(true, lineInfo->LineDetected());
  CPPUNIT_ASSERT(lineInfo->GetPosition() <= 55);


  lineDetectSetting->SetPosition(LineDetectSetting::RIGHT);
  lineInfo = lineDetect->DetectLine(LineInImage);

  CPPUNIT_ASSERT_EQUAL(true, lineInfo->LineDetected());
  CPPUNIT_ASSERT(lineInfo->GetPosition() >= 55);

}
