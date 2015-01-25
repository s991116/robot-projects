#ifndef LINEDETECTTEST_H
#define	LINEDETECTTEST_H

#include "TestCase.h"
#include "extensions/HelperMacros.h"
#include "opencv/cv.h"
#include "../Logging/Logging.h"

using namespace CppUnit;
using namespace std;

class LineDetectTest : public TestCase {
    CPPUNIT_TEST_SUITE(LineDetectTest);

    CPPUNIT_TEST(NoLineInImageLineNotFound);
    CPPUNIT_TEST(LineInImageCenterLineFound);
    CPPUNIT_TEST(LineInImageLineFound);
    CPPUNIT_TEST(FindLeftLinePosition);
    CPPUNIT_TEST(FindRightLinePosition);
    CPPUNIT_TEST(FindPositionForInverseColorLine);
    CPPUNIT_TEST(FindLineWhenLineAtImageBorderLeft);
    CPPUNIT_TEST(FindLineWhenLineAtImageBorderRight);
    CPPUNIT_TEST(NoHorizontalLineInImageLineNotFound);
    CPPUNIT_TEST(HorizontalLineInImageCenterLineFound);

    CPPUNIT_TEST_SUITE_END();
public:
    LineDetectTest();
    void NoLineInImageLineNotFound();
    void LineInImageCenterLineFound();
    void LineInImageLineFound();
    void FindLeftLinePosition();
    void FindRightLinePosition();
    void FindPositionForInverseColorLine();
    void FindLineWhenLineAtImageBorderLeft();
    void FindLineWhenLineAtImageBorderRight();
    void NoHorizontalLineInImageLineNotFound();
    void HorizontalLineInImageCenterLineFound();

private:
    cv::Mat CreateEmptyImage(uchar backgroundColor);
    void AddHorizontalLine(cv::Mat image, int lineStart, int lineEnd, uchar color);
    void AddVerticalLine(cv::Mat image, int lineStart, int lineEnd, uchar color);
    cv::Rect CreateVerticalLineSearchArea(int imageWidth, int sensorLow, int sensorHigh);
    cv::Rect CreateHorizontalLineSearchArea(int imageHeight, int sensorLow, int sensorHigh);
    static const uchar BlackColor = 0;
    static const uchar WhitekColor = 255;
    Logging* _Logging;
};

#endif	/* LINEDETECTTEST_H */

